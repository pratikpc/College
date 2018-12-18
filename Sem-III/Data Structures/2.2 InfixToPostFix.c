/*
 * Program Title:-  Conversion of Infix to Postfix
 * Name:- Pratik Chowdhury
 * Roll No:- 8322
 * Date of Performance: 24.07.18
 */

#include <stdio.h>

#define MAX_SIZE 10

struct Stack
{
	int data[MAX_SIZE];
	int top;
};

int isFull(struct Stack* p) { return (p->top == MAX_SIZE - 1); }
int isEmpty(struct Stack* p) { return (p->top <= -1); }

int pop(struct Stack* p) {
	if (!isEmpty(p))
		return p->data[p->top--];
	else {
		puts("\nStack Underflow Occurred while Popping. Default -1 value returned");
		return -1;
	}
}
void push(struct Stack* p, int data) {
	if (!isFull(p))
		p->data[++p->top] = data;
	else
		printf("\nStack Overflow");
}
int peek(struct Stack* p) {
	if (!isEmpty(p))
		return p->data[p->top];
	else {
		puts("\nStack Underflow Occurred while Peeking. Default -1 value returned");
		return -1;
	}
}

void init_stack(struct Stack* p) {
	p->top = -1;
}

void display(struct Stack* p) {
	int i;
	printf("{");
	for (i = p->top; i > 0; --i)
		printf("%d,", p->data[i]);

	if (p->top >= 0)
		printf("%d", p->data[0]);

	printf("}");
}

int is_operand(const char ch) { return (ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'); }

int precedence(const char ch) {
	switch (ch) {
	case '(':
		return 0;
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	case '^':
		return 3;
	default:
		return -1;
	}
}

int is_operator(const char operator_ch)
{
	switch (operator_ch) {
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

int main() {
	struct Stack operators;

	int i;
	int j;

	char inFix[100];
	char postFix[100];

	char ch;

	init_stack(&operators);

	printf("\nEnter the PostFix Operation to Convert\t:");
	gets(inFix);

	for (i = 0, j = 0; inFix[i] != '\0'; ++i) {
		if (inFix[i] == '(')
			push(&operators, '(');
		else if (inFix[i] == ')') {
			while (!isEmpty(&operators)) {
				ch = pop(&operators);
				if (ch == '(')
					break;
				postFix[j++] = ch;
			}
		}
		else if (is_operand(inFix[i]))
			postFix[j++] = inFix[i];
		else if (is_operator(inFix[i])) {
				while (!isEmpty(&operators) && (precedence(inFix[i]) <= precedence(peek(&operators))))
				{
					if (peek(&operators) == '(')
						break;
					postFix[j++] = pop(&operators);
				}
			push(&operators, inFix[i]);
		}
	}

	while (!isEmpty(&operators))
	{
		if (peek(&operators) == '(')
			pop(&operators);
		else
			postFix[j++] = pop(&operators);
	}
	postFix[j] = '\0';

	printf("\nThe PostFix Conversion is :%s\n", postFix);
	return 0;
}
/*
 * OUTPUT
 *
 * Enter the PostFix Operation to Convert	:A+(B*C-(D/E^F)*G)*H
 * The result is ABC*DEF^/G*-H*+
 *
 * Enter the PostFix Operation to Convert	:A+(B-C*(D/E))
 * The result is ABCDE/*-+
 *
 */
