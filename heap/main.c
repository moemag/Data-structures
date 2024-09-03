#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void swap(int* x, int* y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

void max_heapify(int *arr, int n, int i) //arr,length,root
{ int l;

    if(2*i < n && arr[2*i] >= arr[i]) // left child > root
        l= 2*i; //largest = left child

    else l = i; // largest = root

    if(2*i+1 < n && arr[2*i+1] >= arr[l]) //R.C > L

        l=2*i+1; // L = R.C

    if(l!=i) //check if L! root then heapify
    {
        swap(&arr[i],&arr[l]);
        max_heapify(arr,n,l);
    }


}

void BuildHeap(int*arr,int n)
{ int i;
	for(i=n/2 ; i>=0 ; i--)
        {
        max_heapify(arr,n,i);
        }
}

void heapSort(int*arr,int n)
{
  int i;

    for (i=n-1; i>0; i--) //reduce heap and max heapify
        {
        swap(&arr[0],&arr[i]); // move root to end of array (supposedly largest)
        max_heapify(arr, i, 0);
    }
}



int fillArrayFromFile(char*fname,int*arr)
{
    FILE*fp;
    int i=0;
    fp = fopen(fname,"r");
   while(!feof(fp))
         {fscanf( fp,"%d", &arr[i]);
         i++;
         }

return i;
}




int main(int argc, char**argv) {

	if(argc!=2) {
		printf("Usage: %s filename\n", argv[0]);
		exit(1);
	}
    int *hA=(int*)malloc(sizeof(int)*1000);
 int arrLength=fillArrayFromFile(argv[1],hA);
  clock_t begin = clock();
     BuildHeap(hA,arrLength);
    heapSort(hA,arrLength);
    clock_t end = clock();
     double tTaken = ((double)(end-begin)*1000.0)/CLOCKS_PER_SEC; //calc elapsed time
    int i;
 for (i=0; i<arrLength; i++)
 {
     printf("%d \n", hA[i]);
 }
 printf("heap excute time is: %lf",tTaken);
  free(hA);
  return 0;
}

