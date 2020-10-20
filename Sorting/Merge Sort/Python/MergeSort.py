#MergeSort implementation in Python
def MergeSort(arr):
    if len(arr) > 1:
        # Finding the middle of the array
        mid = len(arr)//2

        # Dividing the array into 2 halves
        L = arr[:mid]
        R = arr[mid:]

        # Sorting the first half
        MergeSort(L)

        # Sorting the second half
        MergeSort(R)

        i = j = k = 0

        # Copying the element to temp arrays L[] and R[]
        while i < len(L) and j < len(R):
            if L[i] < R[j]:
                arr[k] = L[i]
                i += 1
            else:
                arr[k] = R[j]
                j += 1
            k += 1

        # Checking if any element was left
        while i < len(L):
            arr[k] = L[i]
            i += 1
            k += 1
        while j < len(R):
            arr[k] = R[j]
            j += 1
            k += 1

# Print the list
def PrintArray(arr):
    for i in range(len(arr)):
        print(arr[i], end = " ")
    print()


if __name__ == '__main__':
    arr = []
    n = int(input("Enter numbers in the array: "))
    for i in range(0, n):
        ele = int(input("Enter values for array: "))
        arr.append(ele)
    print("Entered array is: ", end=" ")
    PrintArray(arr)
    MergeSort(arr)
    print("Sorted array is: ", end=" ")
    PrintArray(arr)
