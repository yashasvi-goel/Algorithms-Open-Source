#include <iostream>

/* custom XOR swap to switch to adjacent elements */
template <class T>
void swap(T* const array, const size_t i)
{
    array[i] ^= array[i + 1];
    array[i + 1] ^= array[i];
    array[i] ^= array[i + 1];
}

/* sweep the array either in odd indices or in even ones */
template <class T>
bool sweep(T* const array, const size_t size, const bool odd)
{
    // accumalate the variable to check if anything has been changed
    bool swapped = false;

    for (size_t i = odd ? 1 : 0; i < size - 1; i += 2)
        if (array[i] > array[i  + 1])
        {
            swap(array, i);
            swapped = true;
        }
    return swapped;
}

template <class T>
void odd_even_sort(T* const array, const size_t size)
{
    bool swapped = true;
    while (swapped)
    {
        swapped = false;
        // sweep in odd indices and check if anything has been swapped
        swapped = sweep(array, size, true);
        // do the same in even indices
        swapped |= sweep(array, size, false);
        // if nothing changed, the algorithm will terminate
    }
}
