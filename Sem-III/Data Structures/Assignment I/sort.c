// Roll No:- 8322
// Name:-	 Pratik Chowdhury
// Title:- Sort an Array Using Stack

#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10

struct Stack {
  int data[MAX_SIZE];
  int top;
};
void init_stack(struct Stack *p) { p->top = -1; }
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
void display(struct Stack *s) {
  int i;
  for (i = s->top; i >= 0; i--)
    printf(" %d ", s->data[i]);
}

void sort(struct Stack *os, struct Stack *sorted) {
  int x;
  while (!isEmpty(os)) {
    x = pop(os);
    while ((!isEmpty(sorted)) && (peek(sorted) < x))
      push(os, pop(sorted));
    push(sorted, x);
  }
}
int main() {
  struct Stack ori, sorted;
  int n, a, i;
  init_stack(&ori);
  init_stack(&sorted);

  printf("enter the no of elements to be entered \n");
  scanf("%d", &n);
  for (i = 0; i < n; ++i) {
    scanf("%d", &a);
    push(&ori, a);
  }
  printf("the elements in the stack before sorting\t:");
  display(&ori);
  sort(&ori, &sorted);
  printf("\nThe sorted stack is \t:");
  display(&sorted);
  return 0;
}

// OUTPUT
// the elements in the stack before sorting        : 4 3 2 1
// The sorted stack is : 1 2 3 4
