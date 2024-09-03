#include <stdio.h>
#include <stdlib.h>

/*
 * Process: Each process has a name and has an execution time.
 *          We keep track of how long the process still needs
 *          to run on the processor. "remaining_time" is the
 *          remaining execution time of the process.
 * Item: An item that is being enqueued to or dequeued from the queue
 *       It is a pointer to the process
 */
typedef struct {
	char *name;
	int remaining_time;
} Process, *Item;
/*
 *
 */
typedef struct Node {
	Item data;
	struct Node* next;
} Node;
/*
 *
 */
typedef struct {
    Node* front;
    Node* back;
	/* TODO: ADD YOUR CODE HERE */
} Queue;
/*
 *
 */
void init(Queue *q) {
	q=(Queue*) malloc((sizeof(Queue)));
	q->front=q->back=NULL;
	/* TODO: ADD YOUR CODE HERE */
}
/*
 *
 */
int isEmpty(Queue *q) {
	if(q->front==NULL)
	return 1;
	else
        return 0;
}
/*
 *
 */
Item dequeue(Queue *q) {
	if(isEmpty(q))
      return;
    else {
            Node* oldFront = q->front;
    Item x = oldFront->data;
    q->front=q->front->next;
    if (q->front==NULL)
        q->back= NULL;
	free(oldFront);
	oldFront=NULL;
	return x;
	}/* TODO: ADD YOUR CODE HERE */
}
/*
 *
 */
void enqueue(Queue *q, Item val) {

	Node* newBack = ( Node* ) malloc(sizeof(Node));
	newBack->data = val;
	newBack->next = NULL;
	if(isEmpty(q)){
        q->front = q->back= newBack;
	}
	else{ q->back->next = newBack;
	     q->back= newBack;

	}

	/* TODO: ADD YOUR CODE HERE */
}
/*
 *
 */
void destroy(Queue *q) {
free(q->back);
q->back=NULL;
free(q->front);
q->front=NULL;
free(q);
q=NULL;

	/* TODO: ADD YOUR CODE HERE */
}
/*
 * RoundRobin Scheduling
 */
void RoundRobin(char* filename)
{
    FILE *f=fopen(filename,"r");
   Queue q;
    int i=0,quantum=0,j=0;

    int * k=malloc(10*sizeof(int));
    Item t;
    Process* roundR= malloc(10*sizeof(Process));
     init(&q);
    while(!feof(f))
    {
       fscanf(f,"%s %d %d\n",roundR[i].name,k[i],&roundR[i].remaining_time);

     if(k[j]==quantum)
     {
         while(k[j++]==quantum)
         enqueue(&q,&roundR[j]);

         while(!isEmpty(&q)){
            t=dequeue(&q);
   printf("%s (%d --> %d)\n", t->name,quantum,quantum+1);

           if(t->remaining_time>1)
          {t->remaining_time--;
           enqueue(&q,t);
                   }
                   else printf("%s halts\n",t->name);
         }
     } else  {printf("idle (%d --> %d)\n",quantum,quantum+1);

      if(k[j]==quantum)
     {
         while(k[j++]==quantum)
         enqueue(&q,&roundR[j]);
     }
     }


    fclose(f);
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

	RoundRobin(argv[1]);

	return 0;
}
