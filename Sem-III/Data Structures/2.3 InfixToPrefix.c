/*
 * Program Title:- InFix to PreFix
 * Name:- Pratik Chowdhury
 * Roll Number:- 8322
 * Date of Performance:- 24.07.18
 */
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 10

struct Stack	{
	int data[MAX_SIZE];
	int top;
};

int isFull(struct Stack* p)	{return (p->top == MAX_SIZE-1);}
int isEmpty(struct Stack* p)	{return (p->top <= -1);}

int pop(struct Stack* p)	{
	if(!isEmpty(p))	
		return p->data[p->top--];
	else
	{
		puts("\nStack Underflow Occurred while Popping. Default -1 value returned");
		return -1;
	}
}
void push(struct Stack* p , int data)	{
	if(!isFull(p))
		p->data[++p->top] = data;
	else
		printf("\nStack Overflow");		
}
int peek(struct Stack* p)	{
	if(!isEmpty(p))	
		return p->data[p->top];
	else	{
		puts("\nStack Underflow Occurred while Peeking. Default -1 value returned");
		return -1;
	}
}
void init_stack(struct Stack* p)	{p->top = -1;}
void display(struct Stack* p)	{
	int i;	
	printf("{");
	for(i = p->top; i > 0; --i)
		printf("%d,",p->data[i]);
	
	if(p->top >= 0)
		printf("%d",p->data[0]);

	printf("}");
}
int is_operand(const char ch)	{
	return (ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}
int precedence(const char ch)	{
	switch(ch)	{
		case '(':
			return 0;
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
		case '^':
			return 2;
		default:
			return -1;
	}
}
int is_operator(const char operator_ch)	{
	switch(operator_ch)	{
		case '+':
		case '-':
		case '*':
		case '/':
		case '^':
			return 1;
		default:
			return 0;	
	}
}

int inFixToPostFix(char* inFix, char* postFix)	{
	struct Stack operators;
	
	int i;
	int j;
	
	char ch;
	
	init_stack(&operators);
	
	for(i = 0, j = 0; inFix[i] != '\0'; ++i)	{
		if(inFix[i] == '(')
			push(&operators, '(');	
		else if(inFix[i] == ')')	{
			while(!isEmpty(&operators))	{
				ch = pop(&operators);
				if(ch == '(')
					break;
				postFix[j++] = ch;
			}
		}
		else if(is_operand(inFix[i]))
					postFix[j++] = inFix[i];
		else if(is_operator(inFix[i]))	{
			if(!isEmpty(&operators) && precedence(inFix[i]) <= precedence(peek(&operators)))
				while(!isEmpty(&operators) && (precedence(inFix[i]) <= precedence(peek(&operators)) || inFix[i] == '(')){
					if(peek(&operators) == '(')
						break;
					postFix[j++] = pop(&operators);
				}
			push(&operators, inFix[i]);
		}
	}

	while(!isEmpty(&operators)){
		if(peek(&operators) != '(')
			postFix[j++] = pop(&operators);
		else
			pop(&operators);
	}
	postFix[j] = '\0';
	return 0;
}

void swap(char* a, char *b)	{
	char tmp = *a;
	*a = *b;
	*b = tmp;
}
void reverse(char *s)	{
	const int len = strlen(s);
	int i;
	
	for(i = 0; i < len/2; ++i)
		swap(&s[i], &s[len-i-1]);
}

int main()	{
	int i = 0;
	char inFix[100];
	char preFix[100];
	printf("Enter the InFix Expression\t:");
	gets(inFix);
	
	reverse(inFix);
	
	for(i = 0; inFix[i] != '\0'; ++i)
		if(inFix[i] == '(')
			inFix[i] = ')';
		else if(inFix[i] == ')')
			inFix[i] = '(';
	
	inFixToPostFix(inFix, preFix);
	reverse(preFix);
	
	printf("\nThe Prefix Conversion is :%s\n",preFix);
}

/*
 * OUTPUT
 * Enter the InFix Expression	:A+B/C
 * The Prefix Conversion is :+A/BC
 *
 * Enter the InFix Expression	:A/(B+C) 
 * The Prefix Conversion is :/A+BC
 *
 * Enter the InFix Expression	:A/B+C
 * The Prefix Conversion is :+/ABC
 */
