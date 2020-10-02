/*
Author: Pankti Shah
Algorithm: Selection Sort
*/

#include <stdio.h>
#include <stdlib.h>

int main(){
int n,i,j,temp,min,loc;
printf("Enter no. of elements in array\n");
scanf("%d",&n);
int arr[n];

printf("enter %d elements\n",n);
for(i=0;i<n;i++){
    scanf("%d",&arr[i]);
}
for(i=0;i<n;i++){
min=arr[i];
loc=i;
    for(j=i+1;j<n;j++){
        if(arr[j]<min){
            min=arr[j];
            loc=j;
        }
    }

    temp=arr[i];
    arr[i]=arr[loc];
    arr[loc]=temp;

}
for(i=0;i<n;i++){
    printf("%d ",arr[i]);
}
}
