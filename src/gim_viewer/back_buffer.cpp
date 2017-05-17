#include "pch.h"
#include "back_buffer.h"
#include "com_error.h"



namespace back_buffer
{
	dx12::resource_ptr get_back_buffer(dxgi::swap_chain* s, uint32_t buffer)
	{
		dx12::resource_ptr r;
		throw_if_failed( s->GetBuffer(buffer, IID_PPV_ARGS(&r)));
		return r;
	}
}
