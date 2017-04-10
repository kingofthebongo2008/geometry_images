#pragma once

#include <d3d12.h>
#include <wrl/client.h>

namespace dx12
{
	using namespace Microsoft::WRL;

	using device_reference = ComPtr<ID3D12Device1>;

	device_reference create_device();
}