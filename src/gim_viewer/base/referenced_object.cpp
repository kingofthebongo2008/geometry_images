#include "pch.h"
#include "referenced_object.h"


namespace base
{
	void referenced_object::add_ref()
	{
		m_ref_count++;
	}

	void referenced_object::remove_ref()
	{
		m_ref_count--;
		if (m_ref_count < 1)
		{
			delete this;
		}
	}
}