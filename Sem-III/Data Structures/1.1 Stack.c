#include <stdio.h>

#define MAX_SIZE 10

struct Stack
{
	int data[MAX_SIZE];
	int top;
};

int isFull(struct Stack* p)
{
	return (p->top == MAX_SIZE-1);
}
int isEmpty(struct Stack* p)
{
	return (p->top == -1);
}

int pop(struct Stack* p)
{
	if(!isEmpty(p))	
		return p->data[p->top--];
	else
	{
		puts("\nStack Underflow Occurred. Default -1 value returned");
		return -1;
	}
}
void push(struct Stack* p , int data)
{
	if(!isFull(p))
		p->data[++p->top] = data;
	else
		printf("\nStack Overflow");		
}
int peek(struct Stack* p)
{
	if(!isEmpty(p))	
		return p->data[p->top];
	else
	{
		puts("\nStack Underflow Occurred. Default -1 value returned");
		return -1;
	}
}

void init_stack(struct Stack* p)
{
	p->top = -1;
}

void display(struct Stack* p)
{
	int i;	
	printf("{");
	for(i = p->top; i > 0; --i)
		printf("%d,",p->data[i]);
	
	if(p->top >= 0)
		printf("%d",p->data[0]);

	printf("}");
}

int main()
{
	char ch;
	int tmp;
	struct Stack stack;

	init_stack(&stack);

	while(2)
	{
		printf("\n1. Push");
		printf("\n2. Pop");
		printf("\n3. Peek");
		printf("\n4. Display");
		printf("\n5. Is Full");
		printf("\n6. Is Empty");
		printf("\n7. Exit\n");

		scanf(" %c",&ch);
	 
		if(ch == '1')
		{
			printf("\nAdd Data\t:");
			scanf("%d",&tmp);
			push(&stack, tmp);
		}	
		if(ch == '2')
		{
			tmp = pop(&stack);
			printf("\nPopped out : %d",tmp);
		}
		if(ch == '3')
		{
			tmp = peek(&stack);
			printf("\nPeep Out : %d",tmp);
		}
		if(ch=='4')
		{
			printf("\nData in Stack is\t:");	
			display(&stack);
		}
		if(ch == '5')
			printf((isFull(&stack)) ? "\nStack is Full" : "\nStack still has Space left");
		if(ch == '6')
			printf((isEmpty(&stack)) ? "\nStack is Empty" : "\nStack has values");
		if(ch == '7')
			return 0;
	}
	return 0;
}


