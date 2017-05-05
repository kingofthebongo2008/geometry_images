#include "pch.h"

#include "dx11_helpers.h"
#include "com_error.h"

namespace dx11
{
	device_ptr make_device()
	{
		device_ptr r;
		D3D_FEATURE_LEVEL level = D3D_FEATURE_LEVEL_12_0;
		ComPtr<ID3D11Device> d;

		uint32_t flags = 0;

#if defined(_DEBUG)
		flags |= D3D11_CREATE_DEVICE_DEBUG | D3D11_CREATE_DEVICE_DEBUGGABLE;
#endif

		throw_if_failed(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE , nullptr, 0, &level, 1, D3D11_SDK_VERSION, d.GetAddressOf(), nullptr, nullptr));

		throw_if_failed(d.As(&r));
		return r;
	}

	vertex_buffer_ptr	make_vertex_buffer(device* d, uint32_t vertex_count, uint32_t vertex_stride)
	{
		D3D11_BUFFER_DESC desc = {};
		vertex_buffer_ptr r;

		desc.ByteWidth = vertex_count * vertex_stride;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		throw_if_failed(d->CreateBuffer(&desc, nullptr, r.GetAddressOf()));
		return r;
	}

	vertex_buffer_ptr	make_vertex_buffer(device* d, uint32_t vertex_count, uint32_t vertex_stride, const void* initial_data)
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

	texture_2d_ptr		make_texture_2d(device* d, dxgi_format f, uint32_t width, uint32_t height, uint32_t mip_levels, const void* initial_data)
	{
		texture_2d_ptr r;
		return r;
	}

	device_context_ptr  make_device_immediate_context(device* d)
	{
		device_context_ptr r;
		d->GetImmediateContext3(r.GetAddressOf());
		return r;
	} 

	vertex_shader_ptr	make_vertex_shader(device* d, const void *shader_byte_code, size_t byte_code_length )
	{
		vertex_shader_ptr r;
		
		throw_if_failed(d->CreateVertexShader(shader_byte_code, byte_code_length, nullptr, r.GetAddressOf()));
		return r;
	}

	pixel_shader_ptr	make_pixel_shader(device* d, const void *shader_byte_code, size_t byte_code_length)
	{
		pixel_shader_ptr r;

		throw_if_failed(d->CreatePixelShader(shader_byte_code, byte_code_length, nullptr, r.GetAddressOf()));
		return r;
	}

	blend_state_ptr	make_blend_state(device* d, const D3D11_BLEND_DESC1* desc)
	{
		blend_state_ptr r;

		throw_if_failed(d->CreateBlendState1(desc, r.GetAddressOf()));
		return r;
	}

	rasterizer_state_ptr	make_rasterizer_state(device* d, const D3D11_RASTERIZER_DESC2* desc)
	{
		rasterizer_state_ptr r;

		throw_if_failed(d->CreateRasterizerState2(desc, r.GetAddressOf()));
		return r;
	}

	input_layout_ptr	make_input_layout(device* d, const D3D11_INPUT_ELEMENT_DESC* elements, uint32_t element_count, const void* input_signature, size_t input_signature_length)
	{
		input_layout_ptr r;
		throw_if_failed(d->CreateInputLayout(elements, element_count, input_signature, input_signature_length, r.GetAddressOf()));
		return r;
	}

	depth_stencil_state_ptr make_depth_stencil_state(device* d, const D3D11_DEPTH_STENCIL_DESC* desc)
	{
		depth_stencil_state_ptr r;
		throw_if_failed(d->CreateDepthStencilState(desc, r.GetAddressOf()));
		return r;
	}

	render_target_view_ptr	make_render_target_view(device* d, resource* res, const D3D11_RENDER_TARGET_VIEW_DESC1* desc)
	{
		render_target_view_ptr r;
		throw_if_failed(d->CreateRenderTargetView1(res, desc, r.GetAddressOf()));
		return r;
	}

	render_target_view_ptr	make_render_target_view(device* d, resource* r)
	{
		return make_render_target_view(d, r, nullptr);
	}
}