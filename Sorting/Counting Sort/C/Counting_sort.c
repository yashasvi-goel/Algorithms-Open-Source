/*
Author: Pankti Shah
Algorithm: Counting sort
*/

#include <stdio.h> 
#include <string.h> 
#define RANGE 255 

void countSort(int arr[], int n) 
{ 
	// The output character array that will have sorted arr 
	int output[n]; 

	// Create a count array to store count of inidividul numbers
	int count[RANGE + 1], i; 
	memset(count, 0, sizeof(count)); 

	// Store count of each character 
	for (i = 0; arr[i]; ++i) 
		++count[arr[i]]; 

	// Change count[i] so that count[i] now contains actual 
	// position of this number in output array 
	for (i = 1; i <= RANGE; ++i) 
		count[i] += count[i - 1]; 

	// Build the output character array 
	for (i = 0; arr[i]; ++i) { 
		output[count[arr[i]] - 1] = arr[i]; 
		--count[arr[i]]; 
	} 

	
	for (i = 0; arr[i]; ++i) 
		arr[i] = output[i]; 
} 


int main() 
{ 
	int arr[] = {1, 4, 1, 2, 7, 5, 2}; 
    int n = sizeof(arr)/sizeof(arr[0]);
	countSort(arr, n); 

	for(int i =0;i<n; i++){
	   printf("%d ", arr[i]);
	} 
	return 0; 
} 
