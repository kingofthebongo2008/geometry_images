#include "pch.h"

#include "graphics_helpers.h"
#include "com_error.h"

namespace graphics
{
	dx11::texture_2d_ptr get_back_buffer(dxgi::swap_chain* s, uint32_t buffer_index)
	{
		dx11::texture_2d_ptr r;
		throw_if_failed(s->GetBuffer(buffer_index,__uuidof(r), reinterpret_cast<void**>(r.GetAddressOf())));
		return r;
	}
}
	