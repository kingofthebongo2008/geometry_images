#include "pch.h"
#include "back_buffer.h"
#include "com_error.h"

namespace back_buffer
{
	resource get_back_buffer(dxgi::swap_chain* s, uint64_t buffer)
	{
		resource r;
		throw_if_failed( s->GetBuffer(static_cast<uint32_t>(buffer), IID_PPV_ARGS(&r.m_resource)));
		return r;
	}

	dx12::cpu_descriptor_handle make_back_buffer_render_target_view(const resource* r, dx12::device* d, uint64_t buffer_index, dx12::descriptor_heap* frame_heap)
	{
		const auto type					= frame_heap->GetDesc().Type;
		const auto increment			= d->GetDescriptorHandleIncrementSize(type);

		dx12::cpu_descriptor_handle h { frame_heap->GetCPUDescriptorHandleForHeapStart().ptr + buffer_index * increment };
		d->CreateRenderTargetView(r->m_resource.Get(), nullptr, h);
		return h;
	}

	dx12::resource_barrier present_barrier(const resource * b)
	{
		dx12::resource_barrier r	= {};
		r.Type						= D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		r.Transition.pResource		= b->m_resource.Get();
		r.Transition.StateBefore	= D3D12_RESOURCE_STATE_RENDER_TARGET;
		r.Transition.StateAfter		= D3D12_RESOURCE_STATE_PRESENT;
		return r;
	}

	dx12::resource_barrier render_target_barrier(const resource* b)
	{
		dx12::resource_barrier r = {};
		r.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		r.Transition.pResource = b->m_resource.Get();
		r.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
		r.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
		return r;
	}
}
