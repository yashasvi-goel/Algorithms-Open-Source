#include <stdio.h>
#include <stdlib.h>
/*
 * Created by:Yashasvi Goel
 * Date:17/12/2017
 * This is a program to sort an array of numbers in decreasing order
 * The core concept is of bubble sort, but is a recursive method instead of a iterative method
 * The number of input data is expected followed by the input data
 */
void print(int* r,int x)//function to print the array
{
	printf("%d ",r[x]);
	if(x==0)
		return;
	print(r,x-1);//recurse
}
void sort(int* r,int x)
{
	if(x==1)//base case
		return;
	for(int i=0;i<x-1;i++)
		if(r[i]>r[i+1])//swap
		{
			r[i]^=r[i+1];
			r[i+1]^=r[i];
			r[i]^=r[i+1];
		}
	sort(r,x-1);//recurse
}
int main()//driver function
{
	int n;
	scanf("%d",&n);//number of inputs
	int *r;
	r=(int*)malloc(n*sizeof(int));//allocating an array
//	printf("%u\n",r);
	for(int i=0;i<n;i++)
		scanf("%d",&r[i]);
	sort(r,n);
	print(r,n);
	return 0;
}
