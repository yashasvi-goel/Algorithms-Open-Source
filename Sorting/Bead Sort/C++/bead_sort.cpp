/* this sorting algorithm basically "transposes" the "bead slide" and then takes out the elements one by one.
this algorithm only works for numerable objects.
*/
#include <iostream>

/* given an array, find the largest element in it */
template <class T>
T find_max(T* const array, const size_t size)
{
    T max = array[0];
    for (int i = 0; i < size; ++i)
        if (max < array[i])
            max = array[i];
    return max;
}

template <class T>
void bead_sort(T* const array, const size_t size)
{
    /* the length of the transpoed array is the biggest element in the array */
    const size_t transposed_size = find_max(array, size);
    // create a transposed array and reset it's values
    T transposed[transposed_size] {0};

    // go over each element and lay down its beades in the transposed array
    for (size_t i = 0; i < size; ++i)
        for (size_t j = 0; j < array[i]; ++j)
            ++transposed[j];
    
    // go over the transposed array and return the beads to the array with the largest item at the bottom
    for (int i = size - 1; i >= 0; --i)
    {
        size_t j = 0;
        // sum up the bottom layer and remove it
        for (; j < transposed_size && transposed[j] != 0; ++j)
            --transposed[j];
        array[i] = j;
    }
}
