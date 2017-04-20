#pragma once

namespace base
{
    //inherit this class, if you want the classes not to be copyable
    //suitable for class with virtual functions, which will be managed by pointer

    class non_copyable
    {
        protected:

        non_copyable() {}
        ~non_copyable() {}

        private:  // emphasize the following members are private
        non_copyable(const non_copyable&) = delete;
        const non_copyable& operator=(const non_copyable&) = delete;
    };

}
