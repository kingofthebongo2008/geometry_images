#include "pch.h"

#include "dx11_helpers.h"
#include "com_error.h"

namespace dx11
{
	device_reference create_device()
	{
		device_reference r;
		D3D_FEATURE_LEVEL level = D3D_FEATURE_LEVEL_11_0;
		ComPtr<ID3D11Device> d;

		throw_if_failed(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE , nullptr, 0, &level, 1, D3D11_SDK_VERSION, d.GetAddressOf(), nullptr, nullptr));

		throw_if_failed(d.As(&r));
		return r;
	}
}