#pragma once

#include "dx12_helpers.h"
#include "dxgi_helpers.h"

namespace back_buffer
{
	struct resource
	{
		dx12::resource_ptr m_resource;
	};


	resource	get_back_buffer(dxgi::swap_chain* s, uint32_t buffer);
	dx12::cpu_descriptor_handle make_back_buffer_render_target_view(const resource* r, dx12::device* d, uint32_t buffer_index, dx12::descriptor_heap* frame_heap);

	dx12::resource_barrier present_barrier(const resource * r);
	dx12::resource_barrier render_target_barrier(const resource* r);


}
