package Sorting.Java;

import java.util.*;

class RadixSort{

    public static void main(String args[]){
        Scanner sc=new Scanner(System.in);
        int n=sc.nextInt();

        System.out.println("Before sorting:");                      
        int arr[]=new int[n];
        for(int i=0;i<n;i++){
            arr[i]=sc.nextInt();
        }

        sort(arr);
        
        System.out.println("After sorting:");              
        for(int i=0;i<n;i++){
            System.out.print(arr[i]+" ");
        }

        sc.close();

    }

    public static void sort(int arr[]){
        int maxEle=getMax(arr);

        for(int exp=1;(maxEle/exp)>0;exp*=10){
            countingSort(arr,exp);
        }

    }

    public static void countingSort(int arr[],int exp){
        int n=arr.length;

        int output[]=new int[n];
        int count[]=new int[10];

        for(int i=0;i<n;i++){
            count[(arr[i]/exp)%10]++;
        }

        for(int i=1;i<10;i++){
            count[i]+=count[i-1];
        }

        for(int i=n-1;i>=0;i--){
            output[count[(arr[i]/exp)%10]-1]=arr[i];
            count[(arr[i]/exp)%10]--;
        }

        for(int i=0;i<n;i++){
            arr[i]=output[i];
        }

    }

    public static int getMax(int arr[]){                    /* find the maximum element in the array  */
        int max=Integer.MIN_VALUE;
        for(int i=0;i<arr.length;i++){
            if(max<arr[i]){
                max=arr[i];
            }
        }
        return max;
    }

}

