#pragma once

#include <windows.h>
#include <memory>
#include <asset/geometry_image_noncopyable.h>

namespace asset
{
	struct file_handle_deleter
	{
		void operator() (void* f) const
		{
			CloseHandle(f);
		}
	};

	using file_handle = std::unique_ptr< void, file_handle_deleter>;

	class serializer : non_copyable
	{
	

		public:

		serializer(const wchar_t* name);
		~serializer();

		serializer(serializer&&o);
		serializer& operator =(serializer&&o);

		void write_bytes(const void* buffer, size_t buffer_size);

		private:

		file_handle m_file_handle;
	};


	class deserializer : non_copyable
	{


	public:

		deserializer(const wchar_t* name);
		~deserializer();

		deserializer(deserializer&&o);
		deserializer& operator =(deserializer&&o);

		void read_bytes(void* buffer, size_t buffer_size);

	private:

		file_handle m_file_handle;
	};

	inline uint32_t read_uint32_t(deserializer* s)
	{
		uint32_t r = 0;
		s->read_bytes(&r, sizeof(r));
		return r;
	}
}

