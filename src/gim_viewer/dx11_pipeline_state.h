#pragma once

#include <d3d11_4.h>
#include <wrl/client.h>

#include "base/referenced_object.h"
#include "base/intrusive_ptr.h"

namespace dx11
{
	using namespace Microsoft::WRL;

	struct D3D11_INPUT_LAYOUT_DESC
	{
		const D3D11_INPUT_ELEMENT_DESC *	m_input_element_descs;
		uint32_t							m_element_count;
	};

	struct D3D11_SHADER_BYTECODE
	{
		_Field_size_bytes_full_(BytecodeLength)  const void *pShaderBytecode;
		SIZE_T BytecodeLength;
	};

	struct D3D11_GRAPHICS_PIPELINE_STATE_DESC
	{
		D3D11_SHADER_BYTECODE			m_vs;
		D3D11_SHADER_BYTECODE			m_ps;
		D3D11_BLEND_DESC1				m_blend_state;
		D3D11_RASTERIZER_DESC2			m_rasterizer_state;
		D3D11_DEPTH_STENCIL_DESC		m_depth_stencil_state;
		D3D11_INPUT_LAYOUT_DESC			m_input_layout;
		uint32_t						m_render_target_count;
		DXGI_FORMAT						m_rtv_formats[8];
		DXGI_FORMAT						m_dsv_format;
		DXGI_SAMPLE_DESC				m_sample_desc;
	};

	struct ID3D11GraphicsPipelineState : base::referenced_object
	{
		ComPtr<ID3D11VertexShader>		m_vs;
		ComPtr<ID3D11PixelShader>		m_ps;
		ComPtr<ID3D11BlendState1>		m_blend_state;
		ComPtr<ID3D11RasterizerState1>	m_rasterizer_state;
		ComPtr<ID3D11InputLayout>		m_input_layout;
		ComPtr<ID3D11DepthStencilState>	m_depth_stencil_state;
	};

	using graphics_pipeline_state_ptr = base::intrusive_ptr<ID3D11GraphicsPipelineState>;


}