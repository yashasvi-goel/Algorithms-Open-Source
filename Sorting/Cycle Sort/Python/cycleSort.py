'''
  Cycle Sort
  It is based on the idea that array to be sorted can be divided into cycles. Cycles can be visualized as a graph. 
  We have n nodes and an edge directed from node i to node j if the element at i-th index must be present at j-th index in the sorted array.
  * If we want minimum swaps we can use this idea as well. (Min swaps = Sum(CYCLEi -1) )

'''
def cycleSort(array): 
    
  # Loop through the array to find cycles to rotate. 
  for cycleStart in range(0, len(array) - 1): 
    item = array[cycleStart] 
      
    # Find where to put the item. 
    pos = cycleStart 
    for i in range(cycleStart + 1, len(array)): 
      if array[i] < item: 
        pos += 1
      
    # If the item is already there, this is not a cycle. 
    if pos == cycleStart: 
      continue
      
    # Otherwise, put the item there or right after any duplicates. 
    while item == array[pos]: 
      pos += 1
    array[pos], item = item, array[pos] 
      
    # Rotate the rest of the cycle. 
    while pos != cycleStart: 
        
      # Find where to put the item. 
      pos = cycleStart 
      for i in range(cycleStart + 1, len(array)): 
        if array[i] < item: 
          pos += 1
        
      # Put the item there or right after any duplicates. 
      while item == array[pos]: 
        pos += 1
      array[pos], item = item, array[pos] 

  print(array)


n = int(input())
a = list(map(int,input().split()))
cycleSort(a)