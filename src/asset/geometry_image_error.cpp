#include "pch.h"

#include <asset/geometry_image_error.h>

namespace asset
{
	exception::exception(HRESULT h) : m_hresult(h)
	{

	}

	HRESULT exception::hresult() const 
	{
		return m_hresult;
	}

	void throw_if_failed(HRESULT s)
	{
		if (FAILED(s))
		{
			throw exception(s);
		}
	}
}
