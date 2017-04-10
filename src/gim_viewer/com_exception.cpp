#include "pch.h"

#include "com_exception.h"

com_exception::com_exception(HRESULT hr) : m_hr(hr)
{

}

const char* com_exception::what() const
{
	return "com_exception";
}

com_exception::~com_exception() = default;

com_exception::com_exception(const com_exception&) = default;
com_exception::com_exception(com_exception&&) = default;
com_exception& com_exception::operator=(const com_exception&) = default;
com_exception& com_exception::operator=(com_exception&&) = default;
