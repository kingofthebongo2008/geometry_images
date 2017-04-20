#pragma once

#include "non_copyable.h"

#include <cstdint>
#include <atomic>

namespace base
{
    class referenced_object : private non_copyable
    {
        protected:

		referenced_object::referenced_object() : m_ref_count(1)
		{

		}

		virtual ~referenced_object()
        {}

    public:

		void add_ref();
		void remove_ref();

    private:

        std::atomic<int32_t> m_ref_count;
    };

    inline void intrusive_ptr_add_ref(referenced_object * p)
    {
        p->add_ref();
    }
    
    inline void intrusive_ptr_release(referenced_object * p)
    {
        p->remove_ref();
    }
}
