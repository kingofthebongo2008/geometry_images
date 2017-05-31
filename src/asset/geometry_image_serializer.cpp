#include "pch.h"

#include <asset/geometry_image_serializer.h>
#include <asset/geometry_image_error.h>

namespace asset
{
	serializer::serializer(const wchar_t* filename)
	{
		m_file_handle = file_handle(CreateFile2(filename, GENERIC_READ, FILE_SHARE_READ, OPEN_EXISTING, nullptr), file_handle_deleter());
	}

	serializer::~serializer()
	{
	}

	serializer::serializer(serializer&&o) : m_file_handle( std::move(o.m_file_handle))
	{

	}

	serializer& serializer::operator=(serializer&&o)
	{
		m_file_handle = std::move(o.m_file_handle);
		return *this;
	}

	void serializer::write_bytes(const void* buffer, size_t buffer_size) 
	{
		DWORD out = 0;
		if (!WriteFile(m_file_handle.get(), buffer, static_cast<DWORD>(buffer_size), &out, nullptr))
		{
			throw_if_failed(HRESULT_FROM_WIN32(GetLastError()));
		}

	}
}
