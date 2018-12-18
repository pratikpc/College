// Roll No:- 8322
// Name:-	 Pratik Chowdhury
// Title:-	 to simplify an algebraic string of characters having '+', '-', '(' & ')' operators and parenthesis.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 50

struct Stack {
  int data[MAX_SIZE];
  int top;
};

int isFull(struct Stack *p) { return (p->top == MAX_SIZE - 1); }
int isEmpty(struct Stack *p) { return (p->top == -1); }
int pop(struct Stack *p) {
  if (!isEmpty(p))
    return p->data[p->top--];
  else {
    puts("\nStack Underflow Occurred. Default -1 value returned");
    return -1;
  }
}
void push(struct Stack *p, int data) {
  if (!isFull(p))
    p->data[++p->top] = data;
  else
    printf("\nStack Overflow");
}
int peek(struct Stack *p) {
  if (!isEmpty(p))
    return p->data[p->top];
  else {
    puts("\nStack Underflow Occurred. Default -1 value returned");
    return -1;
  }
}
void init_stack(struct Stack *p) { p->top = -1; }
void swap(char *left, char *right) {
  char tmp = *left;
  *left = *right;
  *right = tmp;
}
void reverse(char arr[]) {
  const int len = strlen(arr);
  int i;
  for (i = 0; i < len / 2; ++i)
    swap(&arr[i], &arr[len - i - 1]);
}

void display(struct Stack *p) {
  int i;
  printf("{");
  for (i = p->top; i > 0; --i)
    printf("%d,", p->data[i]);

  if (p->top >= 0)
    printf("%d", p->data[0]);

  printf("}");
}

void convert(const char *exp, char *solution) {
  int i;
  struct Stack q;
  init_stack(&q);
  for (i = 0; exp[i] != '\0'; ++i) {
    if (exp[i] == '-' && exp[i + 1] == '(') {
      push(&q, '-');
      i = i + 2;
      while (exp[i] != '(' && exp[i] != ')' && exp[i] != '\0') {
        if (exp[i] == '+')
          push(&q, '-');
        else if (exp[i] == '-')
          push(&q, '+');
        else
          push(&q, exp[i]);
        ++i;
      }
    } else if (exp[i] != ' ' && exp[i] != ')')
      push(&q, exp[i]);
  }
  for (i = 0; !isEmpty(&q); ++i)
    solution[i] = pop(&q);
  solution[i] = '\0';
  reverse(solution);
}

void main() {
  char exp[50];
  char *solution;
  printf("Enter expression\n");
  gets(exp);
  solution = (char *)malloc(strlen(exp));
  convert(exp, solution);
  printf("The Simplified Version of String\t:%s", solution);
}

// OUTPUT
// a-(b-c-(d+e-(g-l-r)))-f
// The Simplified Version of String : a - b + c + d + e - g + l + r - f
// a-(b-c-(d+e))-f
// The Simplified Version of String : a - b + c + d + e - f
