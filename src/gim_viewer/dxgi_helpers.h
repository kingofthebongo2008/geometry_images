#pragma once

#include <dxgi1_5.h>
#include <wrl/client.h>

namespace winrt
{
	namespace Windows
	{
		namespace UI
		{
			namespace Core
			{
				struct CoreWindow;
			}
		}
	}
}

namespace dxgi
{
	using namespace Microsoft::WRL;

	using factory			= IDXGIFactory5;
	using factory_ptr		= ComPtr<IDXGIFactory5>;
	
	using swap_chain		= IDXGISwapChain3;
	using swap_chain_ptr	= ComPtr<IDXGISwapChain3>;

	factory_ptr make_dxgi_factory();

	swap_chain_ptr	make_swap_chain( factory* f, IUnknown* d, const winrt::Windows::UI::Core::CoreWindow& w, uint32_t width, uint32_t height);
}
