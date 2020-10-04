#include <iostream>

/* custom XOR swap for two swap to adjacent elements */
template <class T>
bool compare_and_swap(T* const array, const size_t i)
{
    if (array[i] > array[i + 1])
    {
        array[i] ^= array[i + 1];
        array[i + 1] ^= array[i];
        array[i] ^= array[i + 1];
        return true;
    }
    return false;
}

template <class T>
void cocktail_short(T* const array, const size_t size)
{
    bool swapped;
    while (true)
    {
        swapped = false;
        // go in forward direction and swap the needed items, also accumalate the swapped variable
        for (int i = 0; i < size - 1; ++i)
            swapped |= compare_and_swap(array, i);
        
        // if nothing has been changed everything is sorted
        if (!swapped)
            return;
        
        // go backwards and do the same
        for (int i = size - 2; i >= 0; --i)
            swapped |= compare_and_swap(array, i);
        
        // if nothing changed, it is sorted
        if (!swapped)
            return;
    }
}
