#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* x, int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}


void BubbleSort(int*arr, int n)
{
int i;
    for(i=n-1; i>0; i--)
    {
        int sorted =1;
       int j;
        for(j=0; j<i; j++)
        {
            if(arr[j]>arr[j+1])
            {
                swap(&arr[j],&arr[j+1]);
                sorted = 0;
            }
        }
        if (sorted)
        {
            break;
        }
    }
}
/*
void MergeSort(int*arr, int n)
{

}*/
void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }


    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}


void mergeSort(int *arr, int l, int r)
{
    if (l < r)
    {

        int m = l+(r-l)/2;

        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}
void comparetwoarrays(int *arr,int *arr1, int l, int r)
{int i=0;
    if(l!=r){printf("\n%d %d \n",i,l,r);

        printf("\n not identical files ");

    return ;}
    else
    {
        for(i; i<l; i++)
        {
            if(arr[i]!=arr1[i])
                break;
        }
        if(i!=l)
           {
            printf("\n not identical files ");
        return;}
        else{

            printf("\n identical files ");
        return;}

    }
}
int fillArrayFromFile(char*fname,int*arr)
{
    FILE*fp;
    int i=0;
    fp = fopen(fname,"r");
    while(!feof(fp))
    {
        fscanf( fp,  "%d", &arr[i]);
        i++;
    }

    return (i);
}
void printSortedArray(int *arr, int n)
{int i=0;
    for (i; i<n; i++)
        printf("%d \n", arr[i]);

}

int main(int argc, char**argv)
{

    if(argc!=3)
    {
        printf("Usage: %s filename\n", argv[0]);
        exit(1);
    }
    int *hA=(int*)malloc(sizeof(int)*5000);
    int *hA1=(int*)malloc(sizeof(int)*5000);
    int arrLength=fillArrayFromFile(argv[1],hA);

    int arrLength1=fillArrayFromFile(argv[2],hA1);

    clock_t begin = clock();
    BubbleSort(hA, arrLength);

            clock_t end = clock();

    double tTaken = ((double)(end-begin)*1000.0)/CLOCKS_PER_SEC; //calc elapsed time

    clock_t begin1 = clock();

    mergeSort(hA1,0,arrLength1-1);
    clock_t end1 = clock();
    double tTaken1 = ((double)(end1-begin1)*1000.0)/CLOCKS_PER_SEC; //calc elapsed time

  //  printSortedArray(hA, arrLength);

   // printSortedArray(hA1, arrLength1);

    printf("bubble excute time is: %lf ms",tTaken);
        printf("\nmerge excute time 1 is: %lf ms",tTaken1);

    comparetwoarrays(hA,hA1,arrLength,arrLength1);
free(hA);
    free(hA1);
    return 0;
}
