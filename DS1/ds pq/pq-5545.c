#include <stdio.h>
#include <stdlib.h>
/*
 * Item: Each Item has a customer name and a balance.
 *       and an integer order(it is used to handle the case when two items have same priority)
*/
typedef struct
{
 char* cName;
 double balance;
 int order;
}Item;
/*
 * Heapify index i in array of Items with size n
 */
void swap (Item *x, Item *y)
{
Item temp = *x;
*x=*y;
*y= temp;
}

void max_heapify(Item *arr, int n, int i)
{ int l;
    if(2*i <= n && arr[2*i].balance > arr[i].balance)
        l= 2*i;

    else l = i;

    if(2*i+1 <= n && arr[2*i+1].balance > arr[l].balance)

        l=2*i+1;

    if(l!=i)
    {
        swap(&arr[i],&arr[l]);
        max_heapify(arr,n,l);
    }
    if(arr[l].balance == arr[i].balance && arr[l].order < arr[i].order)
    {
        swap(&arr[l],&arr[i]);
        max_heapify(arr,n,l);
      }


}
/*
 * Construct Priority queue from the given array of Items with size n(Build Max Heap)
 */
void construct_PQ(Item*arr,int n)
{ int i;
	for(i=n/2 - 1 ; i>=0 ; i--)
        {
        max_heapify(arr,n,i);
        }

}
/*
 * delete the item with max priority and then return it.
 */
Item extract_maximum(Item*arr,int n)
{
    max_heapify(arr,n,0);
	Item max = arr[0];
	arr[0]=arr[n];
	n--;

return max;
}
/*
 * read array of items from file in arr and return its size.
 */
int fillArrayFromFile(char*fname,Item*arr)
{
    FILE*fp;
    int i=0;
    fp = fopen(fname,"r");
    arr[i].cName=(char*) malloc(10);
   while(fscanf( fp, "%s %lf\n",arr[i].cName,&arr[i].balance)!=EOF )
         {
            arr[i].order = i+1;
            i++;
            arr[i].cName=(char*) malloc(10);
         }

return i;
}
/*
 * print customer names in decreasing order according their priority.
 */
void printCustomersbyPriority(Item*arr,int n)
{
    int i;
    for(i=0;i<n;i++){
     Item max = extract_maximum(arr,n);
     printf("%s , %.2lf, %d\n", max.cName, max.balance , max.order);
    }
}
/*
 *
 */
int main(int argc, char**argv) {

	if(argc!=2) {
		printf("Usage: %s filename\n", argv[0]);
		exit(1);
	}
    Item *customers=(Item*)malloc(sizeof(Item)*1000);
    int arrLength=fillArrayFromFile(argv[1],customers);
    construct_PQ(customers,arrLength);
    printCustomersbyPriority(customers,arrLength);
    return 0;
}
