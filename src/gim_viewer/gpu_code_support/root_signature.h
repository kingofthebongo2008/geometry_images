#pragma once

#include "../dx12_helpers.h"

namespace root_signature
{
	dx12::root_signature_ptr make_default(dx12::device* d);

	dx12::root_signature_ptr default(dx12::device* d);
}
