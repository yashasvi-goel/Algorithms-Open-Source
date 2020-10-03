#include <iostream>

/* get the index of the meaximal value in the array */
template <class T>
size_t maximal_index(T* const array, const size_t size)
{
    size_t max_index = 0;
    for (size_t i = 0; i < size; ++i)
        if (array[max_index] < array[i])
            max_index = i;
    return max_index;
}

/* XOR swap to swap two arbitrary items */
template <class T>
void swap(T& lhs, T& rhs)
{
    lhs ^= rhs;
    rhs ^= lhs;
    lhs ^= rhs;
}

/* flip around the whole array from the given base adress and in given length */
template <class T>
void flip(T* const array, const size_t length)
{
    // iterate over all the wanted array to be flipped, with two indices - one going forward and one going backwards
    for (size_t i = 0, reverse_i = length - 1; i < reverse_i; ++i, --reverse_i)
        swap(array[i], array[reverse_i]);
}

template <class T>
void pancake_sort(T* const array, const size_t size)
{ 
   // go over each segment in the 
    for (int i = size; i > 1; --i)
    {
        // get the maximal element in the segment
        size_t max_index = maximal_index(array, i);

        // if the element isn't already in the right place
        if (max_index != size - 1)
        {
            // if the element is not in the first index of the segment
            if (max_index != 0)
                // flip the segment up until the maximal element and including it
                flip(array, max_index + 1);
            
            // flip everything back again to ensure that the maximal element in the segment is in the right location
            flip(array, i);
        }
    }
}
