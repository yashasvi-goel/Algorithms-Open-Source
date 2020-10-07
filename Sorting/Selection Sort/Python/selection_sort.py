def selection_sort(lst):
    for i in range(len(lst)):
        min_index = i
        for j in range(i, len(lst)):
            if lst[j] < lst[min_index]:
                min_index = j
        lst[i], lst[min_index] = lst[min_index], lst[i]
