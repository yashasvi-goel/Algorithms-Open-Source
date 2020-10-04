#include <stdio.h>
#include <stdlib.h>
/*
Program to sort an array of numbers using merge sort
Created by Yashasvi Goel
Date:12/11/2017
*/
int* mergeSort(int *left,int *right,int l,int r)//function to merge the semi-sorted subarrays
{
	int i,j,k;
	i=j=k=0;
	int *c;
	c=(int*)malloc((l+r)*sizeof(int));
	while(i<l&&j<r)
	{
		if(left[i]<right[j])//comparing and placing into the place
			c[k++]=left[i++];
		else
			c[k++]=right[j++];
	}
	while(i<l)//compensating for the unequal sizes of the sub arrays
		c[k++]=left[i++];
	while(j<r)
		c[k++]=right[j++];
	return c;
}
int* subArrays(int *r,int n)//used for partitioning
{
	if(n<2)
		return r;
	int mid=n/2;
	int *left;
	left=(int*)malloc(mid*sizeof(int));
	int *right;
	right=(int*)malloc((n-mid)*sizeof(int));
	for(int i=0;i<mid;i++)//copying into the new arrays
		*(left+i)=r[i];
	for(int j=mid,i=0;j<n;j++,i++)
		*(right+i)=r[j];
	left=subArrays(left,mid);//recursing into the left leg of binary tree
	right=	subArrays(right,n-mid);//recursing into the right leg of the tree
	int *q;
	q=(int*)malloc(n*sizeof(int));
	q=mergeSort(left,right,mid,n-mid);//merging the semi-sorted sub-arrays into the larger arrays
	return q;
}
int main()//driver function
{
	int n;
	scanf("%d",&n);//number of inputs
	int *r;
	r=(int*)malloc(n*sizeof(int));
	int *left,*right;
	for(int i=0;i<n;i++)
		scanf("%d",&r[i]);
	r=subArrays(r,n);
	int *y;
	for(int i=0;i<n;i++)
		printf("%d ",r[i]);
	return 0;
}
