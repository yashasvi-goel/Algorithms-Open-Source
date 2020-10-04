package Sorting.Java;

import java.util.*;

class BucketSort{

    public static void main(String args[]){
        Scanner sc=new Scanner(System.in);
        int n=sc.nextInt();

        System.out.println("Before sorting:");                      /* Taking user input */
        float arr[]=new float[n];
        for(int i=0;i<n;i++){
            arr[i]=sc.nextFloat();
        }

        sort(arr);
        
        System.out.println("After sorting:");              /* Display output */
        for(int i=0;i<n;i++){
            System.out.print(arr[i]+" ");
        }

        sc.close();

    }

    public static void sort(float arr[]){
        int n=arr.length;

        ArrayList<Float> buckets[]=new ArrayList[n];
        for(int i=0;i<n;i++){
            buckets[i]=new ArrayList<>();                        /* Create empty buckets */
        }

        for(int i=0;i<n;i++){               /* insert the elements of the array in respective buckets */
            int index=(int)(arr[i]*n);
            buckets[index].add(arr[i]);
        }

        for(int i=1;i<n;i++){                                      /* sort elements in each bucket */
            Collections.sort(buckets[i]);
        }

        int index=0;
        for(int i=0;i<n;i++){                                /* join the elements of the bucket in the array */
            for(int j=0;j<buckets[i].size();j++){
                arr[index++]=buckets[i].get(j);
            }
        }

    }

}


/*

Time complexity: O(n)

*/
