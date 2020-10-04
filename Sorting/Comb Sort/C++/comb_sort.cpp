#include <iostream>

/* if the elements with distance gap from index i are in the wrong order, swap them using a XOR swap */
template <class T>
bool compare_and_swap(T* const array, const size_t gap, const size_t i)
{
    if (array[i] > array[i + gap])
    {
        array[i] ^= array[i + gap];
        array[i + gap] ^= array[i];
        array[i] ^= array[i + gap];
        return false;
    }
    return true;
}

template <class T>
void comb_sort(T* const array, const size_t size)
{
    // ideal coefficiant to decrease size of gap each iteration
    const double shrink = 1.3;
    // start the gap from 
    bool sorted = false;
    // continue decreasing the gap until the array is fully sorted
    for (size_t gap = size / shrink; !sorted; gap /= shrink)
    {
        // if the gap is less than one, standardize it to one, and set the sorted variable to true until found otherwise
        if (gap < 1)
        {
            gap = 1;
            sorted = true;
        }
        // compare and swap if neeeded all element with distance gap and update the sorted variable accordingly
        for (size_t i = 0; i + gap < size; ++i)
            sorted &= compare_and_swap(array, gap, i);
    }
}
