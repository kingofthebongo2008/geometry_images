#include "pch.h"

#include <asset/geometry_image_serializer.h>
#include <asset/geometry_image_error.h>

namespace asset
{
	serializer::serializer(const wchar_t* filename)
	{
		auto FILE_SHARE_NONE = 0;

		m_file_handle = file_handle(CreateFile2(filename, GENERIC_WRITE, FILE_SHARE_NONE, OPEN_ALWAYS, nullptr), file_handle_deleter());
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

		if (out != buffer_size)
		{
			throw_if_failed(E_FAIL);
		}
	}

	//---------------------------------------------------------------------------------------------------------------------------------
	deserializer::deserializer(const wchar_t* filename)
	{
		auto FILE_SHARE_NONE = 0;
		m_file_handle = file_handle(CreateFile2(filename, GENERIC_READ, FILE_SHARE_READ, OPEN_EXISTING, nullptr), file_handle_deleter());
	}

	deserializer::~deserializer()
	{
	}

	deserializer::deserializer(deserializer&&o) : m_file_handle(std::move(o.m_file_handle))
	{

	}

	deserializer& deserializer::operator=(deserializer&&o)
	{
		m_file_handle = std::move(o.m_file_handle);
		return *this;
	}

	void deserializer::read_bytes(void* buffer, size_t buffer_size)
	{
		DWORD out = 0;
		if (!ReadFile(m_file_handle.get(), buffer, static_cast<DWORD>(buffer_size), &out, nullptr))
		{
			throw_if_failed(HRESULT_FROM_WIN32(GetLastError()));
		}

		if (out != buffer_size)
		{
			throw_if_failed(E_FAIL);
		}
	}
}
