/*
 * Program Title:- Queue using Linked List
 * Name:- Pratik Chowdhury
 * Roll Number:- 8322
 * Date of Performance:- 06.08.18
 */

#include <stdio.h>
#include <stdlib.h>

struct Node	{
	int val;
	struct Node* next;
};
struct Queue
{
	struct Node* first;
	struct Node* last;
};
int is_empty(struct Node* list)	{return list == NULL;}
int is_empty_queue(struct Queue* queue)	{return (queue == NULL || queue->first == NULL || queue->last == NULL);}
void init_queue(struct Queue* q)	{q->first = q->last = NULL;}
struct Node* nodeFromValue(const int x)	{
	struct Node* value = (struct Node*)malloc(sizeof(struct Node));
	value->val = x;
	value->next = NULL;
	return value;
}

void enqueue(struct Queue* queue, struct Node* value)	{
	if(is_empty(value))
		return;
	if(is_empty_queue(queue))
		queue->first = queue->last = value;	
	else
	{
		queue->last->next = value;
		queue->last = queue->last->next;
	}
}
int dequeue(struct Queue* queue, int * val)	{
	struct Node * del;
	if(is_empty_queue(queue))
		return 0;
	*val = queue->first->val;
	del = queue->first;
	queue->first = queue->first->next;
	free(del);
	return 1;
}
void display(struct Queue* queue)	{
	struct Node * it;
	printf("{");
	if(!is_empty_queue(queue))	{
		for(it = queue->first; it->next != queue->last->next; it = it->next)
			printf("%d,", it->val);
		printf("%d",it->val);
	}
	printf("}");
}
int main(void)	{
	char ch;
	int tmp;
	struct Queue queue;

	init_queue(&queue);

	printf("\n1. Enqueue");
	printf("\n2. Deque");
	printf("\n3. Display");
	printf("\n4. Is Empty");
	printf("\n5. Exit\n");
	while(1)
	{
		scanf(" %c",&ch);
		if(ch == '1')	{
			printf("Add Data\t:");
			scanf("%d",&tmp);
			enqueue(&queue, nodeFromValue(tmp));
		}	
		if(ch == '2')	{
			if(dequeue(&queue,&tmp))
				printf("Dequed out : %d",tmp);
			else
				printf("\nError Deleting. Queue Empty");
		}
		if(ch=='3')	{
			printf("\nData in Queue is\t:");	
			display(&queue);
		}
		if(ch == '4')
			printf((is_empty_queue(&queue)) ? "\nQueue is Empty" : "\nQueue has values");
		if(ch == '5')
			return 0;
	}
	return 0;
}
/* OUTPUT
 * 1. Enqueue
 * 2. Deque
 * 3. Display
 * 4. Is Empty
 * 5. Exit
 * 1
 * Add Data	:23
 * 1
 * Add Data	:45
 * 1
 * Add Data	:56
 * 2
 * Dequed out : 23
 * 3
 * Data in Queue is	:{45,56}
 * 4
 * Queue has values
 */
