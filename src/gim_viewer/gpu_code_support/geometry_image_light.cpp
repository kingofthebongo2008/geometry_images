#include "pch.h"

#include "geometry_image_light.h"
#include "root_signature.h"
#include "../d3dx12.h"

#include "autogen/bunny_pixel.h"
#include "autogen/bunny_vertex.h"

namespace geometry_image_light
{
	dx12::pipeline_state_ptr	make(dx12::device* d)
	{
		D3D12_GRAPHICS_PIPELINE_STATE_DESC r = {};

		// Define the vertex input layout.
		D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
			//{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
		};

		// Describe and create the graphics pipeline state object (PSO).
		D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
		psoDesc.InputLayout = { inputElementDescs, _countof(inputElementDescs) };
		psoDesc.pRootSignature = root_signature::default(d).Get();
		psoDesc.VS = CD3DX12_SHADER_BYTECODE(&g_bunny_vertex[0], sizeof(g_bunny_vertex));
		psoDesc.PS = CD3DX12_SHADER_BYTECODE(&g_bunny_pixel[0], sizeof(g_bunny_pixel));
		psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
		psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
		psoDesc.DepthStencilState.DepthEnable = FALSE;
		psoDesc.DepthStencilState.StencilEnable = FALSE;
		psoDesc.SampleMask				= UINT_MAX;
		psoDesc.PrimitiveTopologyType	= D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		psoDesc.NumRenderTargets = 1;
		psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
		psoDesc.SampleDesc.Count = 1;

		return dx12::make_graphics_pipeline_state(d, &psoDesc);
	}
}
