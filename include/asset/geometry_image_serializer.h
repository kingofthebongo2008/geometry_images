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
}

