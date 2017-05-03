#include "pch.h"

#include "dx12_helpers.h"
#include "com_error.h"

namespace dx12
{
	device_reference create_device()
	{
		device_reference r;
		throw_if_failed(D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_0, __uuidof(ID3D12Device1), reinterpret_cast<void**>(r.GetAddressOf())));
		return r;
	}
}