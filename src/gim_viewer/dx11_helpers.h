#pragma once

#include <d3d11_4.h>
#include <wrl/client.h>

#include "dx11_base_helpers.h"
#include "dx11_pipeline_state.h"

namespace dx11
{
	using namespace Microsoft::WRL;


	graphics_pipeline_state_ptr create_graphics_pipelinestate(const D3D11_GRAPHICS_PIPELINE_STATE_DESC * d);
}