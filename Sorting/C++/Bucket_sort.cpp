/*
Author: Pankti Shah
Algorithm: Bucket sort
Bucket sort is mainly useful when input is uniformly distributed over a range. 
*/

 
#include <algorithm> 
#include <iostream> 
#include <vector> 
using namespace std; 


void bucketSort(float arr[], int n) 
{ 
	// Create n empty buckets 
	vector<float> b[n]; 

	// Put array elements in different buckets 
	for (int i = 0; i < n; i++) { 
		int bi = n * arr[i]; // Index in bucket 
		b[bi].push_back(arr[i]); 
	} 

	// Sort individual buckets 
	for (int i = 0; i < n; i++) 
		sort(b[i].begin(), b[i].end()); 

	// Concatenate all buckets into arr[] 
	int index = 0; 
	for (int i = 0; i < n; i++) 
		for (int j = 0; j < b[i].size(); j++) 
			arr[index++] = b[i][j]; 
} 

int main() 
{ 
	float arr[] = { 0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434 }; 
	int n = sizeof(arr) / sizeof(arr[0]); 
	bucketSort(arr, n); 

	for (int i = 0; i < n; i++) 
		printf("%f ", arr[i]); 
	return 0; 
} 
