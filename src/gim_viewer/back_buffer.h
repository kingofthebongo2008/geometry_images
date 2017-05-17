#pragma once

#include "dx12_helpers.h"
#include "dxgi_helpers.h"

namespace back_buffer
{
	dx12::resource_ptr get_back_buffer(dxgi::swap_chain* s, uint32_t buffer);
}
