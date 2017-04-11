#pragma once

#include <d3d11_4.h>
#include <wrl/client.h>

namespace dx11
{
	using namespace Microsoft::WRL;

	using device_reference = ComPtr<ID3D11Device4>;

	device_reference create_device();
}