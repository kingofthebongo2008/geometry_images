#pragma once

#include <exception>


class com_exception : public std::exception
{
	public:

	com_exception(HRESULT hr);

	~com_exception();
	com_exception(const com_exception&);
	com_exception(com_exception&&);
	com_exception& operator=(const com_exception&);
	com_exception& operator=(com_exception&&);
	

	const char* what() const override;

	private:

	HRESULT m_hr;
};


