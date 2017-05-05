#pragma once

#include "dx11_helpers.h"
#include "dxgi_helpers.h"

namespace graphics
{
	dx11::texture_2d_ptr get_back_buffer(dxgi::swap_chain* s, uint32_t frame_index);
}