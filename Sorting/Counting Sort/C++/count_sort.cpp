#include<bits/stdc++.h>
using namespace std;
#define RANGE 1000

void countSort(int arr[], int n) 
{ 
	int output[n]={0}; 
	int count[RANGE + 1]={0}; 
	 

	for (int i = 0; i<n ; i++) 
	{
		count[arr[i]]++; 
	}

	for (int i = 1; i <= RANGE; i++) 
	{
		count[i] += count[i - 1]; 
	}

	for (int i = 0; i<n ; i++) 
	{ 
		output[count[arr[i]] - 1] = arr[i]; 
		count[arr[i]]--; 
	} 

	
	for (int i = 0; i<n; ++i) 
		cout<<output[i]<<" ";
	cout<<endl;
} 


int main() 
{ 
	int arr[] = {1, 4, 1, 2, 7, 5, 2}; 
    int n = sizeof(arr)/sizeof(arr[0]);
	countSort(arr, n); 

	
} 