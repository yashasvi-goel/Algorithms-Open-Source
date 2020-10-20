#Implementation of QuickSort in Python
def partition(arr,low,high):
    # index of smaller element
    i = (low-1)

    # Pivot is the last element in arr
    pivot = arr[high]
    print("Pivot is: " + str(pivot))

    for j in range(low,high):
        # Checks if the current element is smaller than or
        # equal to pivot
        if arr[j] <= pivot:

            # Increment index of smaller element
            i +=1

            # Swap the values at the high index and the smaller index
            arr[i],arr[j] = arr[j],arr[i]

    # Swap the values
    arr[i+1],arr[high] = arr[high],arr[i+1]
    return (i+1)

# arr is the array to be sorted
# low is the starting index
# high is the ending index
def QuickSort(arr,low,high):
    if len(arr) == 1:
        return arr
    if low < high:

        # p is partitioning index, arr[p] is at the right place
        p = partition(arr,low,high)

        # Sperately sort elements before partition and after partition
        QuickSort(arr,low,p-1)
        QuickSort(arr,p+1,high)

if __name__=='__main__':
    arr = [10,7,8,9,1,5]
    n = len(arr)
    QuickSort(arr,0,n-1)
    print("Sorted array is:")
    for i in range(n):
        print(arr[i])