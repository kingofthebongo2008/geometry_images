#pragma once

#include <d3d11_4.h>
#include <wrl/client.h>

namespace dx11
{
	using namespace Microsoft::WRL;

	using device					= ID3D11Device4;
	using device_ptr				= ComPtr<ID3D11Device4>;

	using vertex_shader				= ID3D11VertexShader;
	using vertex_shader_ptr			= ComPtr<ID3D11VertexShader>;

	using pixel_shader				= ID3D11PixelShader;
	using pixel_shader_ptr			= ComPtr<ID3D11PixelShader>;

	using vertex_buffer				= ID3D11Buffer;
	using vertex_buffer_ptr			= ComPtr<ID3D11Buffer>;
	
	using index_buffer				= ID3D11Buffer;
	using index_buffer_ptr			= ComPtr<ID3D11Buffer>;

	using texture_2d				= ID3D11Texture2D;
	using texture_2d_ptr			= ComPtr<ID3D11Texture2D>;
	using dxgi_format				= DXGI_FORMAT;

	using device_context			= ID3D11DeviceContext3;
	using device_context_ptr		= ComPtr<ID3D11DeviceContext3>;

	using blend_state				= ID3D11BlendState1;
	using blend_state_ptr			= ComPtr<ID3D11BlendState1>;

	using rasterizer_state			= ID3D11RasterizerState2;
	using rasterizer_state_ptr		= ComPtr<ID3D11RasterizerState2>;

	using rasterizer_state			= ID3D11RasterizerState2;
	using rasterizer_state_ptr		= ComPtr<ID3D11RasterizerState2>;

	using input_layout				= ID3D11InputLayout;
	using input_layout_ptr			= ComPtr<ID3D11InputLayout>;

	using depth_stencil_state		= ID3D11DepthStencilState;
	using depth_stencil_state_ptr	= ComPtr<ID3D11DepthStencilState>;

	using render_target_view		= ID3D11RenderTargetView1;
	using render_target_view_ptr	= ComPtr<ID3D11RenderTargetView1>;

	using depth_stencil_view		= ID3D11DepthStencilView;
	using depth_stencil_view_ptr	= ComPtr<ID3D11DepthStencilView>;

	using resource					= ID3D11Resource;
	using resource_ptr				= ComPtr<ID3D11Resource>;

	device_ptr make_device();

	vertex_buffer_ptr		make_vertex_buffer(device* d, uint32_t vertex_count, uint32_t vertex_stride);
	vertex_buffer_ptr		make_vertex_buffer(device* d, uint32_t vertex_count, uint32_t vertex_stride, const void* initial_data);
	texture_2d_ptr			make_texture_2d(device* d, dxgi_format f, uint32_t width, uint32_t height, uint32_t mip_levels, const void* initial_data);
	vertex_shader_ptr		make_vertex_shader(device* d,const void *shader_byte_code, size_t byte_code_length);
	pixel_shader_ptr		make_pixel_shader(device* d, const void *shader_byte_code, size_t byte_code_length);
	device_context_ptr		make_device_immediate_context(device* d);

	blend_state_ptr			make_blend_state(device* d, const D3D11_BLEND_DESC1* desc);
	rasterizer_state_ptr	make_rasterizer_state(device* d, const D3D11_RASTERIZER_DESC2* desc);
	input_layout_ptr		make_input_layout(device* d, const D3D11_INPUT_ELEMENT_DESC* elements, uint32_t element_count, const void* input_signature, size_t input_signature_length);
	depth_stencil_state_ptr make_depth_stencil_state(device* d, const D3D11_DEPTH_STENCIL_DESC* desc);

	render_target_view_ptr	make_render_target_view(device* d, resource* r);
	render_target_view_ptr	make_render_target_view(device* d, resource* r, const D3D11_RENDER_TARGET_VIEW_DESC1* desc );
}