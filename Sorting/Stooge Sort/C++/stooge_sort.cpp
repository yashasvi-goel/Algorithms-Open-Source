#include <iostream>

/* swap function using a XOR to avoid temporary variables */
template <class T>
void swap(T& lhs, T& rhs)
{
    lhs ^= rhs;
    rhs ^= lhs;
    lhs ^= rhs;
}

template <class T>
void stooge_sort(T* const array, const size_t size)
{
    // if the first and last elements are descending, swap them
    if (array[0] > array[size - 1])
        swap(array[0], array[size - 1]);
    
    // if there is any sorting left to be done
    if (size > 2)
    {
        const size_t third = size / 3;
        // sort the first two thirds
        stooge_sort(array, size - third);
        // sort the second two thirds
        stooge_sort(array + third, size - third);
        // sort the first two third again to "connect" the two fully sorted thirds and reorganize the middle one
        stooge_sort(array, size - third);
    }
}
