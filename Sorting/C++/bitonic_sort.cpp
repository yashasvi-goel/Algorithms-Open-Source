#include <iostream>
/* bitonic sort only works for powers of 2 */

/* swap any two elements only if they do not correspond to the correct direction */
template <class T>
void compare_and_swap(T& lhs, T& rhs, bool asc)
{
    if (lhs > rhs == asc)
    {
        lhs ^= rhs;
        rhs ^= lhs;
        lhs ^= rhs;
    }
}

/* merge an array made of two opposite direction bitonic arrays */
template <class T>
void bitonic_merge(T* const array, const size_t size, bool asc = true)
{
    // only if there is more than one item is there anything to merge
    if (size > 1)
    {
        const size_t mid = size / 2;
        // swap if needed to create two bitonic array in opposite bitonic
        for (size_t i = 0; i < mid; ++i)
            compare_and_swap(array[i], array[mid + i], asc);
        
        // merge recursively
        bitonic_merge(array, mid, asc);
        bitonic_merge(array + mid, size - mid, asc);
    }
}


template <class T>
void bitonic_sort(T* const array, const size_t size, bool asc = true)
{
    if (size > 1)
    {
        const size_t mid = size / 2;

        // sort each side in opposite directions
        bitonic_sort(array, mid, true);
        bitonic_sort(array + mid, size - mid, false);

        // and then merge hem together
        bitonic_merge(array, size, asc);
    }
}
