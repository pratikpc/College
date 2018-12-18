/*
 * Program Title:- Evaluation of PostFix
 * Name:- Pratik Chowdhury
 * Roll Number:- 8322
 * Date of Performance:- 24.07.18
 */
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

int is_digit(const char ch)
{
	return (ch >= '0' && ch <= '9');
}

int is_operator(const char operator)
{
	switch(operator)
	{
		case '+':
		case '-':
		case '*':
		case '/':
			return 1;
		default:
			return 0;	
	}
}

int operate(const int op1, const int op2, const char operator)
{
	switch(operator)
	{
		case '+':
			return op1+op2;
		case '-':
			return op1-op2;
		case '*':
			return op1*+op2;
		case '/':
			return op1/op2;	
		default:
			return 0;	
	}
}

int main()
{
	struct Stack operands;
	char postFix[100];
	
	char ch;
	int op1, op2;
	int res;

	int i, j;

	
	init_stack(&operands);
	
	printf("\nEnter the PostFix Operation to Evaluate\t:");
	gets(postFix);
	
	for(i = 0, j = 0; postFix[i] != '\0'; ++i)
	{
		if(is_digit(postFix[i]))
			push(&operands, postFix[i] - '0');
		else if(is_operator(postFix[i]))
		{
			op2 = pop(&operands);
			op1 = pop(&operands);
			
			res = operate(op1, op2, postFix[i]);
			
			push(&operands, res);
		}
	}
	printf("The result is %d\n", pop(&operands));
	return 0;
}

/*
 * OUTPUT
 * Enter the PostFix Operation to Evaluate	:23+5-    
 * The result is 0
 * Enter the PostFix Operation to Evaluate	:23+4*
 * The result is 20
 * Enter the PostFix Operation to Evaluate	:129*+ 
 * The result is 19
 */
