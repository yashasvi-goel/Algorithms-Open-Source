
/*
	Cycle Sort
	It is based on the idea that array to be sorted can be divided into cycles. Cycles can be visualized as a graph. 
	We have n nodes and an edge directed from node i to node j if the element at i-th index must be present at j-th index in the sorted array.
	* If we want minimum swaps we can use this idea as well. (Min swaps = Sum(CYCLEi -1) )
*/
#include<bits/stdc++.h>
using namespace std;
#define ll           long long int
#define fast         ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define INF          1e18
#define MOD          1000000007
#define Vi           vector<ll> 
#define Vs           vector<string>
#define VI           vector<vector<ll> >
#define PII          pair<ll,ll> 
#define PSI          pair<string,ll>
#define PB           push_back

// Function sort the array using Cycle sort 
void cycleSort(int arr[], int n) 
{ 
  
    // traverse array elements and put it to on 
    // the right place 
    for (int cycle_start = 0; cycle_start <= n - 2; cycle_start++) { 
        // initialize item as starting point 
        int item = arr[cycle_start]; 
  
        // Find position where we put the item. We basically 
        // count all smaller elements on right side of item. 
        int pos = cycle_start; 
        for (int i = cycle_start + 1; i < n; i++) 
            if (arr[i] < item) 
                pos++; 
  
        // If item is already in correct position 
        if (pos == cycle_start) 
            continue; 
  
        // ignore all duplicate  elements 
        while (item == arr[pos]) 
            pos += 1; 
  
        // put the item to it's right position 
        if (pos != cycle_start) { 
            swap(item, arr[pos]); 
           
        } 
  
        // Rotate rest of the cycle 
        while (pos != cycle_start) { 
            pos = cycle_start; 
  
            // Find position where we put the element 
            for (int i = cycle_start + 1; i < n; i++) 
                if (arr[i] < item) 
                    pos += 1; 
  
            // ignore all duplicate  elements 
            while (item == arr[pos]) 
                pos += 1; 
  
            // put the item to it's right position 
            if (item != arr[pos]) { 
                swap(item, arr[pos]);  
            } 
        } 
    } 
   
} 

int main()
{
    fast;
    int n;
    cin >> n;
    int a[n];
    for(int i=0;i<n;i++)
    	cin >> a[i];
   	cycleSort(a,n);
   	for (int i = 0; i < n; i++) 
        cout << a[i] << " "; 
}