/*
Implementing the quickSort algorithm (based on the Lomuto partition scheme) in C++ using template functions to increase modularity.
*/
#include <iostream>

/* XOR swap for two arbitray items */
template <class T>
void swap(T& lhs, T& rhs)
{
    lhs ^= rhs;
    rhs ^= lhs;
    lhs ^= rhs;
}

/* given a segment in an array, partition in into two sides - one bigger than the last element and one smaller */
template <class T>
int partition(T* const array, const size_t size)
{
    // set the pivot to be the last element
    const T pivot = array[size - 1];

    size_t i = 0;
    // move all the items smaller than the pivot to a dynamic partition and save it's size - i
    for (size_t j = 0; j < size; ++j)
        if (array[j] < pivot)
        {
            swap(array[i], array[j]);
            ++i;
        }
    // in the end, swap the pivot to be in the last spot in the partition
    swap(array[i], array[size - 1]);
    return i;
}

template <class T>
void quick_sort(T* const array, const size_t size)
{
    // as long as there is anything to sort
    if (size > 1)
    {
        // get the index of the partition
        const size_t p = partition(array, size);

        // sort everything to the left and the right
        quick_sort(array, p);
        quick_sort(array + p + 1, size - p);
    }
}
