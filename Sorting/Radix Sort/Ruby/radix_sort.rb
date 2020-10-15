def radix_sort(array)
  x = array.max
  power = 1
  until power > x
    counting_sort(array, ->(val) { (val / power) % 10 })
    power *= 10
  end
end

def counting_sort(array, key)
  count = Array.new(10, 0)
  output = Array.new(array.length, 0)
  array.each { |x| count[key.call(x)] += 1 }
  1.upto(count.length - 1) { |i| count[i] += count[i - 1] }
  (array.length - 1).downto(0) do |i|
    count[key.call(array[i])] -= 1
    output[count[key.czall(array[i])]] = array[i]
  end
  output.each_index { |i| array[i] = output[i] }
end

a = [1, 687, 3, 734, 2, 5959, 8]
radix_sort(a)
print a
