#include "pch.h"

#include "dx11_helpers.h"
#include "com_error.h"

namespace dx11
{
	graphics_pipeline_state_ptr create_graphics_pipeline_state_object(device* d, const D3D11_GRAPHICS_PIPELINE_STATE_DESC* description)
	{
		graphics_pipeline_state_ptr r(new ID3D11GraphicsPipelineState());

		{
			vertex_shader_ptr		vs;
			if (description->m_vs.BytecodeLength > 0 && description->m_vs.pShaderBytecode)
			{
				vs = make_vertex_shader(d, description->m_vs.pShaderBytecode, description->m_vs.BytecodeLength);
			}
			r->m_vs = std::move(vs);
		}

		{
			pixel_shader_ptr		ps;
			if (description->m_ps.BytecodeLength > 0 && description->m_ps.pShaderBytecode)
			{
				ps = make_pixel_shader(d, description->m_ps.pShaderBytecode, description->m_ps.BytecodeLength);
			}
			r->m_ps = std::move(ps);
		}

		{
			r->m_blend_state = make_blend_state(d, &description->m_blend_state);
		}

		{
			r->m_rasterizer_state = make_rasterizer_state(d, &description->m_rasterizer_state);
		}

		{
			r->m_depth_stencil_state = make_depth_stencil_state(d, &description->m_depth_stencil_state);
		}

		if ( description->m_input_layout.m_element_count > 0 && description->m_vs.BytecodeLength > 0 && description->m_vs.pShaderBytecode)
		{
			r->m_input_layout = make_input_layout(d,
				description->m_input_layout.m_input_element_descs,
				description->m_input_layout.m_element_count,
				description->m_vs.pShaderBytecode,
				description->m_vs.BytecodeLength);
		}

		return r;
	}

	texture_2d_ptr get_back_buffer(dxgi::swap_chain* s, uint32_t frame_index)
	{
		return nullptr;
	}
}
	