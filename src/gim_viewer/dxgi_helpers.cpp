#include "pch.h"

#include "dxgi_helpers.h"
#include "com_error.h"

#include <winrt/Windows.UI.Core.h>

namespace dxgi
{
	factory_ptr make_dxgi_factory()
	{
		factory_ptr r;
	
		uint32_t flags = 0;

		#if defined(_DEBUG)
			flags = DXGI_CREATE_FACTORY_DEBUG;
		#endif

		throw_if_failed(CreateDXGIFactory2(flags, __uuidof(IDXGIFactory5), reinterpret_cast<void**>(r.GetAddressOf())));
		return r;
	}


	swap_chain_ptr	make_swap_chain( factory* f, IUnknown* d, const winrt::Windows::UI::Core::CoreWindow& w, uint32_t width, uint32_t height )
	{
		ComPtr<IDXGISwapChain1> r;
		

		DXGI_SWAP_CHAIN_DESC1 desc = {};

		desc.Width			= width;
		desc.Height			= height;
		desc.Format			= DXGI_FORMAT_R10G10B10A2_UNORM;
		desc.Stereo			= FALSE;
		desc.SampleDesc		= { 1,0 };
		desc.BufferUsage	= DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.BufferCount	= 2;
		desc.Scaling		= DXGI_SCALING_NONE;
		desc.SwapEffect		= DXGI_SWAP_EFFECT_FLIP_DISCARD;
		desc.AlphaMode		= DXGI_ALPHA_MODE_IGNORE;
        desc.Flags          = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH | DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING | DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT;
		
		//desc.Flags			= DXGI_SWAP_CHAIN_FLAG_NONPREROTATED | DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH | DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING | DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT | DXGI_SWAP_CHAIN_FLAG_DISPLAY_ONLY;
		
		throw_if_failed(f->CreateSwapChainForCoreWindow(d, reinterpret_cast<IUnknown*>(winrt::get_abi(w)) , &desc, nullptr, r.GetAddressOf()));

		Microsoft::WRL::ComPtr<IDXGISwapChain4> result2;
		throw_if_failed(r.As(&result2));
		
		return result2;
	}
}
