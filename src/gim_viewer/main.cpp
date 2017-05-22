#include "pch.h"
#include <cstdint>

#include <winrt/base.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.ApplicationModel.Activation.h>
#include <winrt/Windows.UI.ViewManagement.h>

using namespace winrt::Windows::UI::Core;
using namespace winrt::Windows::ApplicationModel::Core;
using namespace winrt::Windows::ApplicationModel::Activation;

#include "dx12_helpers.h"
#include "dxgi_helpers.h"
#include "graphics_helpers.h"
#include "back_buffer.h"
#include "com_error.h"
#include "gpu_code_support/geometry_image_light.h"

#include <pix3.h>

class ViewProvider : public winrt::implements<ViewProvider, IFrameworkView, IFrameworkViewSource>
{
	public:

	IFrameworkView CreateView()
	{
		return *this;
	}

	void Initialize(const CoreApplicationView& v)
	{
		m_activated			= v.Activated(winrt::auto_revoke, { this, &ViewProvider::OnActivated });

		m_device				= dx12::make_device();
		m_direct_queue			= dx12::make_direct_command_queue(m_device.Get());
		m_direct_allocators[0]	= dx12::make_direct_command_allocator(m_device.Get());
		m_direct_allocators[1]  = dx12::make_direct_command_allocator(m_device.Get());
		m_factory				= dxgi::make_dxgi_factory();
		m_direct_queue_fence	= dx12::make_fence(m_device.Get(), m_direct_queue_fence_values[m_frame_index]);

        m_direct_list[0]        = dx12::make_graphics_command_list(m_device.Get(), m_direct_allocators[0].Get());
        m_direct_list[1]        = dx12::make_graphics_command_list(m_device.Get(), m_direct_allocators[1].Get());

        throw_if_failed(m_direct_list[0]->Close());
        throw_if_failed(m_direct_list[1]->Close());

		{
			const auto frame_count			= 2;
			const auto render_target_count	= 1;
			const auto descriptor_count		= frame_count * render_target_count;
			m_frame_descriptor_heap			= dx12::make_render_targets_descriptor_heap(m_device.Get(), descriptor_count);
			m_depth_descriptor_heap			= dx12::make_depth_stencil_descriptor_heap(m_device.Get(), descriptor_count);

			m_resources_heap				= dx12::make_shader_resources_descriptor_heap(m_device.Get(), 2);
			m_samplers_heap					= dx12::make_sampler_descriptor_heap(m_device.Get(), 2);
		}

		auto t = geometry_image_light::make(m_device.Get());
	}

	void Uninitialize() 
	{

	}

	void Run()
	{
		WaitForGpu();
		while (m_window_running)
		{
			CoreWindow::GetForCurrentThread().Dispatcher().ProcessEvents(CoreProcessEventsOption::ProcessAllIfPresent);

            {
                throw_if_failed(m_direct_allocators[m_frame_index]->Reset());
                m_direct_list[m_frame_index]->Reset(m_direct_allocators[m_frame_index].Get(), nullptr);
            }

			{
				auto list = m_direct_list[m_frame_index].Get();

				PIXScopedEvent(list, PIX_COLOR_INDEX(0), L"Swap Chain");

				auto back_buffer = back_buffer::get_back_buffer(m_swap_chain.Get(), m_frame_index);
				auto rtv		 = back_buffer::make_back_buffer_render_target_view(&back_buffer, m_device.Get(), m_frame_index, m_frame_descriptor_heap.Get());

				{
					dx12::set_resource_barrier(list, back_buffer::render_target_barrier(&back_buffer));
				}

				{
					float c[] = { 1,0,0,0 };
					list->ClearRenderTargetView(rtv, &c[0], 0, nullptr);
				}

				{
					dx12::set_resource_barrier(list, back_buffer::present_barrier(&back_buffer));
				}
			}

            {
                PIXScopedEvent(m_direct_queue.Get(), PIX_COLOR_INDEX(0), L"Execute Command Lists");
				m_direct_list[m_frame_index]->Close();
                dx12::command_list* lists[] = { m_direct_list[m_frame_index].Get() };
                m_direct_queue->ExecuteCommandLists(1, &lists[0]);
            }

            m_swap_chain->Present(1, 0);
            MoveToNextFrame();
		}

        WaitForGpu();
	}

	void Load(winrt::hstring_view h)
	{
	}

	void SetWindow(const CoreWindow& w)
	{
		m_closed			= w.Closed(winrt::auto_revoke, { this, &ViewProvider::OnWindowClosed });
		m_size_changed		= w.SizeChanged(winrt::auto_revoke, { this, &ViewProvider::OnWindowSizeChanged });

		m_swap_chain		= dxgi::make_swap_chain(m_factory.Get(), m_direct_queue.Get(), w, w.Bounds().Width, w.Bounds().Height);
		m_frame_index		= m_swap_chain->GetCurrentBackBufferIndex();
	}

	void OnWindowClosed(const CoreWindow&w, const CoreWindowEventArgs& a)
	{
		m_window_running = false;
	}

	void OnActivated(const CoreApplicationView&, const IActivatedEventArgs&)
	{
		CoreWindow::GetForCurrentThread().Activate();
	}

	void OnWindowSizeChanged(const CoreWindow& w, const WindowSizeChangedEventArgs& a)
	{
		WaitForGpu();
		DXGI_SWAP_CHAIN_DESC1 desc;
		throw_if_failed(m_swap_chain->GetDesc1(&desc));
		throw_if_failed(m_swap_chain->ResizeBuffers(desc.BufferCount, a.Size().Width, a.Size().Height, desc.Format, desc.Flags));
	}

	void WaitForGpu()
	{
        PIXScopedEvent(m_direct_queue.Get(), PIX_COLOR_INDEX(0), L"Wait for GPU");
		//schedule signal to the command queue
		throw_if_failed(m_direct_queue->Signal(m_direct_queue_fence.Get(), m_direct_queue_fence_values[m_frame_index]));

		// Wait until the fence has been processed.
		m_direct_queue_fence->SetEventOnCompletion(m_direct_queue_fence_values[m_frame_index], m_direct_queue_fence_event);
		//todo: check
		WaitForSingleObjectEx(m_direct_queue_fence_event, INFINITE, FALSE);

		// Increment the fence value for the current frame.
		m_direct_queue_fence_values[m_frame_index]++;
	}

	void MoveToNextFrame()
	{
        PIXScopedEvent(m_direct_queue.Get(), PIX_COLOR_INDEX(0), L"Move To Next Frame");
		const uint64_t fence_value = m_direct_queue_fence_values[m_frame_index];
		
		//schedule signal to the command queue
		throw_if_failed(m_direct_queue->Signal(m_direct_queue_fence.Get(), fence_value));

		//update frame index
		m_frame_index = m_swap_chain->GetCurrentBackBufferIndex();

		// If the next frame is not ready to be rendered yet, wait until it is ready.
		if (m_direct_queue_fence->GetCompletedValue() < m_direct_queue_fence_values[m_frame_index])
		{
			m_direct_queue_fence->SetEventOnCompletion(fence_value, m_direct_queue_fence_event);
			//todo: check for result
			WaitForSingleObjectEx(m_direct_queue_fence_event, INFINITE, FALSE);
		}

		m_direct_queue_fence_values[m_frame_index] = fence_value + 1;
	}

	bool m_window_running = true;
	CoreWindow::Closed_revoker					m_closed;
	CoreWindow::SizeChanged_revoker				m_size_changed;
	CoreApplicationView::Activated_revoker		m_activated;

	uint64_t									m_frame_index = 0;

	dx12::device_ptr							m_device;
	dx12::direct_command_queue_ptr				m_direct_queue;
	dx12::direct_command_allocator_ptr			m_direct_allocators[2];
    dx12::graphics_command_list_ptr   			m_direct_list[2];
	dx12::fence_ptr								m_direct_queue_fence;
	uint64_t									m_direct_queue_fence_values[2] = {};
	dx12::fence_event							m_direct_queue_fence_event;

    dx12::descriptor_heap_ptr                   m_frame_descriptor_heap;
	dx12::descriptor_heap_ptr					m_depth_descriptor_heap;
    dx12::resource_ptr                          m_back_buffer;

    dxgi::factory_ptr							m_factory;
	dxgi::swap_chain_ptr						m_swap_chain;

	dx12::descriptor_heap_ptr					m_resources_heap;
	dx12::descriptor_heap_ptr					m_samplers_heap;
};

int32_t __stdcall wWinMain( HINSTANCE, HINSTANCE,PWSTR, int32_t )
{
	CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	CoreApplication::Run(ViewProvider());
	CoUninitialize();
	return 0;
}
