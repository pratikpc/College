/*
 * Program Title:- Linear Queue
 * Name:- Pratik Chowdhury
 * Roll Number:- 8322
 * Date of Performance:- 24.07.18
 */
 
 #include <stdio.h>
 
 #define MAX 10
 
 struct Queue
 {
 	int data[MAX];
 	int front;
 	int end;
 };
 
int isEmpty(const struct Queue* const q)	{return (q->front == q->end);}
int isFull(const struct Queue* const q)		{return (q->end == MAX);}

int enqueue(struct Queue* q, const int val)	{
	if(isFull(q))
		return 0;
	if(isEmpty(q))	{
		q->front = 0;
		q->end = 0;
	}
	q->data[q->end++]  = val;
	
	return 1;
}
void init_queue(struct Queue* q)	{
	q->front = q->end = -1;
}
int dequeue(struct Queue* q, int* val)	{
	if(isEmpty(q))	{
		init_queue(q);
		return 0;
	}
	*val = q->data[q->front++];
	return 1;
}

void display(struct Queue* q)	{
	int i;	
	printf("{");
	for(i = q->front; i < q->end-1; ++i)
		printf("%d,",q->data[i]);
	if(!isEmpty(q))
		printf("%d",q->data[q->end-1]);
		
	printf("}");
}


int main(void)	{
	char ch;
	int tmp;
	struct Queue queue;

	init_queue(&queue);

	while(2)
	{
		printf("\n1. Enqueue");
		printf("\n2. Deque");
		printf("\n3. Display");
		printf("\n4. Is Full");
		printf("\n5. Is Empty");
		printf("\n6. Exit\n");

		scanf(" %c",&ch);
	 
		if(ch == '1')	{
			printf("\nAdd Data\t:");
			scanf("%d",&tmp);
			if(!enqueue(&queue, tmp))
				printf("\nError Inserting. Queue Full");
		}	
		if(ch == '2')	{
			if(dequeue(&queue,&tmp))
				printf("\nDequed out : %d",tmp);
			else
				printf("\nError Deleting. Queue Empty");
		}
		if(ch=='3')	{
			printf("\nData in Queue is\t:");	
			display(&queue);
		}
		if(ch == '4')
			printf((isFull(&queue)) ? "\nQueue is Full" : "\nQueue still has Space left");
		if(ch == '5')
			printf((isEmpty(&queue)) ? "\nQueue is Empty" : "\nQueue has values");
		if(ch == '6')
			return 0;
	}
	return 0;
}
 
 /*
  * OUTPUT
  * 1. Enqueue
  * 2. Deque
  * 3. Display
  * 4. Is Full
  * 5. Is Empty
  * 6. Exit
  * 1
  * Add Data	:23
  * 1
  * Add Data	:34
  * 3
  * Data in Queue is	:{23,34}
  * 2
  * Dequed out : 23
  * 4
  * Queue still has Space left
  * 5
  * Queue has values
  * 2
  * Dequed out : 34
  * 5
  * Queue is Empty
  * 6
  */
