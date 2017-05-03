#pragma once

#include <dxgi1_5.h>
#include <wrl/client.h>

namespace dxgi
{
	using namespace Microsoft::WRL;

	using factory_ptr = ComPtr<IDXGIFactory5>;

	factory_ptr make_dxgi_factory();
}
