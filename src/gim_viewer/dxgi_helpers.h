#pragma once

#include <dxgi1_5.h>
#include <wrl/client.h>

namespace dxgi
{
	using namespace Microsoft::WRL;

	using factory_reference = ComPtr<IDXGIFactory5>;

	factory_reference create_dxgi_factory();
}
