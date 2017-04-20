#include "pch.h"

#include "dx11_helpers.h"
#include "com_error.h"

namespace dx11
{
	device_ptr create_device()
	{
		device_ptr r;
		D3D_FEATURE_LEVEL level = D3D_FEATURE_LEVEL_11_0;
		ComPtr<ID3D11Device> d;

		uint32_t flags = 0;

#if defined(_DEBUG)
		flags |= D3D11_CREATE_DEVICE_DEBUG | D3D11_CREATE_DEVICE_DEBUGGABLE;
#endif

		throw_if_failed(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE , nullptr, 0, &level, 1, D3D11_SDK_VERSION, d.GetAddressOf(), nullptr, nullptr));

		throw_if_failed(d.As(&r));
		return r;
	}

	vertex_buffer_ptr	create_vertex_buffer(device* d, uint32_t vertex_count, uint32_t vertex_stride)
	{
		D3D11_BUFFER_DESC desc = {};
		vertex_buffer_ptr r;

		desc.ByteWidth = vertex_count * vertex_stride;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		throw_if_failed(d->CreateBuffer(&desc, nullptr, r.GetAddressOf()));
		return r;
	}

	vertex_buffer_ptr	create_vertex_buffer(device* d, uint32_t vertex_count, uint32_t vertex_stride, const void* initial_data)
	{
		D3D11_BUFFER_DESC desc = {};
		vertex_buffer_ptr r;

		desc.ByteWidth = vertex_count * vertex_stride;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA s = {};
		s.pSysMem			= initial_data;
		s.SysMemPitch		= vertex_count * vertex_stride;
		throw_if_failed(d->CreateBuffer(&desc, nullptr, r.GetAddressOf()));
		return r;
	}

	texture_2d_ptr		create_texture_2d(device* d, dxgi_format f, uint32_t width, uint32_t height, uint32_t mip_levels, const void* initial_data)
	{
		texture_2d_ptr r;
		return r;
	}

	device_context_ptr  create_device_immediate_context(device* d)
	{
		device_context_ptr r;
		d->GetImmediateContext3(r.GetAddressOf());
		return r;
	} 
}