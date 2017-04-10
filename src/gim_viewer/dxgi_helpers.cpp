#include "pch.h"

#include "dxgi_helpers.h"
#include "com_error.h"

namespace dxgi
{
	factory_reference create_dxgi_factory()
	{
		factory_reference r;
	
		uint32_t flags = 0;

		#if defined(_DEBUG)
			flags = DXGI_CREATE_FACTORY_DEBUG;
		#endif

		throw_if_failed(CreateDXGIFactory2(flags, __uuidof(IDXGIFactory5), reinterpret_cast<void**>(r.GetAddressOf())));
		return r;
	}
}
