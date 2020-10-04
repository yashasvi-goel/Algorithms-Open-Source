#include <iostream>

/* XOR swap custom made for the gnome sort */
template <class T>
void swap(T* const array, const size_t i)
{
    array[i] ^= array[i - 1];
    array[i - 1] ^= array[i];
    array[i] ^= array[i - 1];
}

template <class T>
void gnome_sort(T* const array, const size_t size)
{
    size_t i = 0;
    // continue until all is needed swaps are done and no more elements are to be sorted
    while (i < size)
    {
        // if the two current elements are in the right direction
        if (i == 0 || array[i - 1] <= array[i])
            ++i;
        else // if they are in the wrong direction, swap them and go one index back to fix any other consequences of this swap
        {
            swap(array, i);
            --i
        }
    }
}
