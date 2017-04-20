#pragma once

#include <d3d11_4.h>
#include <wrl/client.h>

namespace dx11
{
	using namespace Microsoft::WRL;

	using device				= ID3D11Device4;
	using device_ptr			= ComPtr<ID3D11Device4>;

	using vertex_shader			= ID3D11VertexShader;
	using vertex_shader_ptr		= ComPtr<ID3D11VertexShader>;

	using pixel_shader			= ID3D11PixelShader;
	using pixel_shader_handle	= ComPtr<ID3D11PixelShader>;

	using vertex_buffer			= ID3D11Buffer;
	using vertex_buffer_ptr		= ComPtr<ID3D11Buffer>;
	
	using index_buffer			= ID3D11Buffer;
	using index_buffer_ptr		= ComPtr<ID3D11Buffer>;

	using texture_2d			= ID3D11Texture2D;
	using texture_2d_ptr		= ComPtr<ID3D11Texture2D>;
	using dxgi_format			= DXGI_FORMAT;

	using device_context		= ID3D11DeviceContext3;
	using device_context_ptr	= ComPtr<ID3D11DeviceContext3>;


	device_ptr create_device();

	vertex_buffer_ptr	create_vertex_buffer(device* d, uint32_t vertex_count, uint32_t vertex_stride);
	vertex_buffer_ptr	create_vertex_buffer(device* d, uint32_t vertex_count, uint32_t vertex_stride, const void* initial_data);
	texture_2d_ptr		create_texture_2d(device* d, dxgi_format f, uint32_t width, uint32_t height, uint32_t mip_levels, const void* initial_data);
	device_context_ptr  create_device_immediate_context(device* d);
}