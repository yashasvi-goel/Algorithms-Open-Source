def bubble_sort(array)
  n = array.length - 1
  while n > 1
    new_n = 0
    n.times do |i|
      array[i], array[i + 1] = array[i + 1], array[i] if array[i + 1] < array[i]
      new_n = i
    end
    n = new_n
  end
end

a = [1, 6, 3, 7, 23, 865, 8]
bubble_sort(a)
print a