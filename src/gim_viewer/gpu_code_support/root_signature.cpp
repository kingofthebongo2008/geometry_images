#include "pch.h"

#include "root_signature.h"
#include "autogen/root_signature_code.h"

namespace root_signature
{
	dx12::root_signature_ptr make_default(dx12::device* d)
	{
		const void* code = &g_root_signature[0];
		size_t		code_size = sizeof(g_root_signature);
		return dx12::make_root_signature(d, code, code_size);
	}

	dx12::root_signature_ptr default(dx12::device* d)
	{
		static dx12::root_signature_ptr r = make_default(d);
		return r;
	}
}


