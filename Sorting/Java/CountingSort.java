package Sorting.Java;

import java.util.*;

class CountingSort{

    public static void main(String args[]){
        Scanner sc=new Scanner(System.in);
        int n=sc.nextInt();

        System.out.println("Before sorting:");                      /* Taking user input */
        int arr[]=new int[n];
        for(int i=0;i<n;i++){
            arr[i]=sc.nextInt();
        }

        sort(arr);

        sc.close();

    }

    public static void sort(int arr[]){
        int n=arr.length;

        int max=findMax(arr);
        int min=findMin(arr);

        int range=max-min+1;
        int count[]=new int[range];
        int output[]=new int[n];

        for(int i=0;i<n;i++){               /*  count the number of occurrence of each element  */
            count[arr[i]-min]++;
        }

        for(int i=1;i<range;i++){                /* calculate prefix sum array */
            count[i]+=count[i-1];
        }

        for(int i=0;i<n;i++){                                /* place the elements in their correct positions  */
            output[count[arr[i]-min]-1]=arr[i];
            count[arr[i]-min]--;
        }

        System.out.println("After sorting:");              /* Display output */
        for(int i=0;i<n;i++){
            System.out.print(output[i]+" ");
        }

    }

    public static int findMax(int arr[]){                    /* find the maximum element in the array  */
        int max=Integer.MIN_VALUE;
        for(int i=0;i<arr.length;i++){
            if(max<arr[i]){
                max=arr[i];
            }
        }
        return max;
    }
    public static int findMin(int arr[]){                    /* find the minimum element in the array  */
        int min=Integer.MAX_VALUE;
        for(int i=0;i<arr.length;i++){
            if(min>arr[i]){
                min=arr[i];
            }
        }
        return min;
    }

}


/*

Time complexity: O(n+k) where n is the number of elements and k is the range.

*/