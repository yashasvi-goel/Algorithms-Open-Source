/*
Author: Pankti Shah
Algorithm: Insertion Sort
*/

#include <stdio.h>
#include <stdlib.h>

int main(){
int n,i,j,temp,min,loc;
printf("no. of elements in array\n");
scanf("%d",&n);
int arr[n];

printf("enter %d elements\n",n);
for(i=0;i<n;i++){
    scanf("%d",&arr[i]);
}

for(i=1;i<n;i++){
    temp=arr[i];
    j=i-1;
    while(temp<arr[j] && j>=0){
        arr[j+1]=arr[j];
        j=j-1;
    }
    arr[j+1]=temp;
}

for(i=0;i<n;i++){
    printf("%d ",arr[i]);
}
}

