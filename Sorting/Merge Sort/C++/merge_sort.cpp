/*
Implementing the mergeSort algorithm in C++ using template functions to increase modularity.
*/
#include <iostream>

/* the left array is the also the pointer to the beginning of the orignal array to be sorted on */
template <class T>
void merge(T* const left_array, const size_t left_size,
           T* const right_array , const size_t right_size)
{
    int* const array = left_array;
    T temp_left[left_size], temp_right[right_size];
    
    // copy the two seperately sorted arrays to temporary arrays
    memcpy(temp_left, left_array, left_size * sizeof(T));
    memcpy(temp_right, right_array, right_size * sizeof(T));

    size_t left_index = 0, right_index = 0, index = 0;
    // apply to the the original array until one of the sides is "used up"
    while (left_index < left_size && right_index < right_size)
    {
        if (temp_left[left_index] < temp_right[right_index])
        {
            array[index] = temp_left[left_index];
            ++left_index;
        }
        else
        {
            array[index] = temp_right[right_index];
            ++right_index;
        }
        ++index;
    }
    // has the right side been fully copied to the original array
    const bool completed_right = right_index == right_size;

    // all of the following are to get the side that has yet to be completed
    const size_t& unfilled_size  = completed_right ? left_size  : right_size;
    size_t& unfilled_index       = completed_right ? left_index : right_index;
    T* unfilled_array            = completed_right ? temp_left  : temp_right;

    // add in the unfinished part
    for (; unfilled_index < unfilled_size; ++unfilled_index, ++index)
        array[index] = unfilled_array[unfilled_index];
}

template <class T>
void merge_sort(T* const array , const size_t size)
{
    // base case - array with one element only
    if (size > 1)
    {
        const size_t mid = size / 2;

        merge_sort(array, mid);
        merge_sort(array + mid, size - mid);

        // merge the separately sorted 
        merge(array, mid, array + mid, size - mid);
    }
}