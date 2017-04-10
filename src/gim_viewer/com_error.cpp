#include "pch.h"
#include "com_error.h"
#include "com_exception.h"

void throw_if_failed(HRESULT hr)
{
	if (FAILED(hr))
	{
		throw com_exception(hr);
	}
}
