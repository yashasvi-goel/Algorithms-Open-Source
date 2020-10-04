#include <iostream>

template <class T>
void shell_sort(T* const array, const size_t size)
{
    // for each gap between indices
    for (size_t gap = 0; gap < size; ++gap)
    {
        // go over each index in the gap until the end
        for (size_t i = gap; i < size; ++i)
        {
            // keep the current element
            const T temp = array[i];

            size_t j = i;
            // move forward all the elements that are bigger than the current element and are indexed higher than it
            for (; j >= gap && array[j - gap] > temp; j -= gap)
                array[j] = array[j - gap];
            // return the current element to it's original value
            array[j] = temp;
        }
    }
        
}
