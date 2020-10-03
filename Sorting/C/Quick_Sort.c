#include<stdio.h>
#include<stdlib.h>

void printarr(int);
void quicksort(int,int);
int partition(int,int);
void swap(int *, int *);

int *a;

int main()
{
    int i,n;

    printf("Enter the size of the array:\n");
    scanf("%d",&n);
    a=(int*) calloc(n,sizeof(int));

    printf("Enter the array:\n");
    for (i=0; i<n; i++)
    {
        printf("Element %d: ",i+1);
        scanf("%d",&a[i]);
    }

    printf("Before sorting:\n");
    printarr(n);

    quicksort(0,n-1);

    printf("After sorting:\n");
    printarr(n);

    return 0;
}

void quicksort(int beg, int end)
{
    int pivot;
    if(beg<end)
    {
        pivot=partition(beg,end);
        quicksort(beg,pivot-1);
        quicksort(pivot+1,end);
    }
}

int partition(int beg, int end)
{
    int l,r,pivot,flag=0;
    l=pivot=beg;
    r=end;

    while(flag==0)
    {
        while((pivot!=r)&&(r>=l))
        {
            if(a[r]<=a[pivot])
                {
                    swap(&a[r],&a[pivot]);
                    pivot=r;
                    break;
                }
            r--;
        }
        if(r==l)
            flag=1;

        while((l!=pivot)&&(l<=r)&&(flag!=1))
        {
            if(a[l]>=a[pivot])
            {
                swap(&a[l],&a[pivot]);
                pivot=l;
                break;
            }
            l++;
        }
        if(l==r)
            flag=1;
    }

    return pivot;
}

void swap(int *a, int *b)
{
    *a=*a+*b;
    *b=*a-*b;
    *a=*a-*b;
}

void printarr(int n)
{
    int i;
    for (i=0; i<n; i++)
    {
        printf("Element %d: %d\n",i+1,a[i]);
    }
}
