#pragma once

#include <exception>
#include <windows.h>

namespace asset
{
	class exception : public std::exception
	{
		public:
		exception(HRESULT h);

		HRESULT hresult() const;

		private:
		HRESULT m_hresult;
	};

	void throw_if_failed(HRESULT s);
}

