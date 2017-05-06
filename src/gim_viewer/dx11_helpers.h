#pragma once

#include <d3d11_4.h>
#include <wrl/client.h>

#include "dx11_base_helpers.h"
#include "dx11_pipeline_state.h"
#include "dxgi_helpers.h"

namespace dx11
{
	using namespace Microsoft::WRL;

    using graphics_pipeline_state = ID3D11GraphicsPipelineState;
    using graphics_pipeline_state_ptr = base::intrusive_ptr<ID3D11GraphicsPipelineState>;

	graphics_pipeline_state_ptr create_graphics_pipeline_state_object(device* d, const D3D11_GRAPHICS_PIPELINE_STATE_DESC * desc);

    class graphics_context : public base::referenced_object
    {
        graphics_context(device_context_ptr p);

        void set_pso(graphics_pipeline_state* p);
        void clear_state();
        void set_render_target();

        private:
        device_context_ptr m_context;
    };


}