#include  <stdio.h>

#define MAX_SIZE 10

struct Stack
{
	int data[MAX_SIZE];
	int top1; /*FRONT*/
	int top2; /*REAR*/
};

void init_stack(struct Stack* p)
{
	p->top1 = -1;
	p->top2 = MAX_SIZE;
}

int isFull1(const struct Stack* p)
{
	return (p->top1 >= p->top2-1);
}
int isEmpty1(const struct Stack* p)
{
	return p->top1 == -1;
}

void push1(struct Stack* p, int val)
{
	if(!isFull1(p))	
		p->data[++p->top1] = val;
	else
		puts("Stack Overflow Occured");
}
int pop1(struct Stack* p)
{
	if(!isEmpty1(p))
		return p->data[p->top1--];
	else
	{
		puts("\nStack Underflow Occured. Ignore value obtained");
		return -1;
	}	
}
int peek1(const struct Stack*p)
{
	if(!isEmpty1(p))
		return p->data[p->top1];
	else
	{
		puts("\nStack Underflow Occured. Ignore value obtained");
		return -1;
	}	
}

void display1(const struct Stack* p)
{
	int i;	
	printf("{");
	for(i = p->top1; i > 0; --i)
	{
		printf("%d,",p->data[i]);
	}
	if(p->top1 >= 0)
		printf("%d",p->data[0]);
	printf("}");
}

int isEmpty2(const struct Stack* p)
{
	return (p->top2 == MAX_SIZE);
}
int isFull2(const struct Stack* p)
{
	return (p->top2 <= p->top1+1);
}
void push2(struct Stack* p, int val)
{
	if(!isFull2(p))	
		p->data[--p->top2] = val;
	else
		puts("Stack Overflow Occured");
}

int pop2(struct Stack* p)
{
	if(!isEmpty2(p))
		return p->data[p->top2++];
	else
	{
		puts("\nStack Underflow Occured. Ignore value obtained");
		return -1;
	}	
}
int peek2(const struct Stack*p)
{
	if(!isEmpty2(p))
		return p->data[p->top2];
	else
	{
		puts("\nStack Underflow Occured. Ignore value obtained");
		return -1;
	}	
}
void display2(struct Stack* p)
{
	int i;	
	printf("{");
	for(i = p->top2; i < MAX_SIZE-1; ++i)
	{
		printf("%d,",p->data[i]);
	}
	if(p->top2 <= MAX_SIZE-1)
		printf("%d",p->data[MAX_SIZE-1]);
	printf("}");
}

int main()
{
	char ch;
	int val;

	struct Stack stack;

	init_stack(&stack);

	while(1)
	{
		puts("\nEnter 1 to PUSH Stack 1");
		puts("Enter 2 to PUSH Stack 2");
		puts("Enter 3 to POP Stack 1");
		puts("Enter 4 to POP Stack 2");
		puts("Enter 5 to DISPLAY Stack 1");
		puts("Enter 6 to DISPLAY Stack 2");
		puts("Enter 7 to PEEK Stack 1");
		puts("Enter 8 to PEEKStack 2");
		puts("Enter 9 to Exit");

		scanf(" %c",&ch);
		switch(ch)
		{
			case '1':
				if(!isFull1(&stack))
				{
					printf("\nAdd Data 1\t:");
					scanf("%d",&val);
					push1(&stack, val);
				}
				else
					printf("\nStack Overflow Occured");				
			break;
			case '2':
				if(!isFull2(&stack))
				{
					printf("\nAdd Data 2\t:");
					scanf("%d",&val);
					push2(&stack, val);
				}
				else
					printf("\nStack Overflow Occured");				
			break;
			case '3':
				if(!isEmpty1(&stack))
				{
					val = pop1(&stack);
					printf("\nPopped out 1 : %d",val);
				}
				else
					printf("\nStack Underflow occured");
			break;
			case '4':
				if(!isEmpty2(&stack))
				{
					val = pop2(&stack);
					printf("\nPopped out 2 : %d",val);
				}
				else
					printf("\nStack Underflow occured");
			break;
			case '5':
				printf("\nData in Stack 1 is\t:");	
				display1(&stack);
			break;
			case '6':
				printf("\nData in Stack 2 is\t:");	
				display2(&stack);				
			break;
			case '7':
				if(!isEmpty1(&stack))
				{
					val = peek1(&stack);
					printf("\nPeeped out 1 : %d",val);
				}
				else
					printf("\nStack Underflow occured");
			break;
			case '8':
				if(!isEmpty2(&stack))
				{
					val = peek2(&stack);
					printf("\nPeeped out 2 : %d",val);
				}
				else
					printf("\nStack Underflow occured");
			break;
			case '9':
				return 0;
			break;
		}
	}
	return 0;
}
