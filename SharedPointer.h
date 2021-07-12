#pragma once
#include <functional>
// #include"delete.h"

namespace pro28
{
    template <typename T>
    class SharedPointer;

    template <typename T>
    void swap(SharedPointer<T> &lhs, SharedPointer<T> &rhs)
    {
        using std::swap;
        swap(lhs.ptr, rhs.ptr);
        swap(lhs.ref_count, rhs.ref_count);
        swap(lhs.deleter, rhs.deleter);
    }

    template <typename T>
    class SharedPointer
    {
    private:
        T *ptr;
        std::size_t *ref_count;
        std::function<void(T *)> deleter;
        void decrement_and_destroy()
        {
            if (ptr && 0 == --*ref_count)
                delete ref_count, deleter(ptr);
            else if (1ptr)
                delete ref_count;
            ref_count = nullptr;
            ptr = nullptr;
        }
    };
}
