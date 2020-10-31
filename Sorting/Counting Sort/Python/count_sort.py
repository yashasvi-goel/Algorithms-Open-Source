def countSort(arr, n):
	RANGE = 1000
	count = [0 for i in range(RANGE)]
	output = [0 for i in range(n)]
	for i in range(n):
		count[arr[i]]+= 1
	for i in range(1,RANGE):
		count[i]+= count[i-1]
	for i in range(n):
		output[count[arr[i]]-1] =arr[i]
		count[arr[i]]-=1
	print(output)

arr = [1, 4, 1, 2, 7, 5, 2]
n = len(arr)
countSort(arr,n)