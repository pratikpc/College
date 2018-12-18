/*
 * Program Title:- Stack using Linked List
 * Name:- Pratik Chowdhury
 * Roll Number:- 8322
 * Date of Performance:- 06.08.18
 */

#include <stdio.h>
#include <stdlib.h>

struct Node {
  int val;
  struct Node *next;
};
int is_empty(struct Node **list) { return *list == NULL; }
void init_stack(struct Node **start) { *start = NULL; }
struct Node *nodeFromValue(const int x) {
  struct Node *value = (struct Node *)malloc(sizeof(struct Node));
  value->val = x;
  value->next = NULL;
  return value;
}
void push(struct Node **start, struct Node *value) {
  if (is_empty(&value))
    return;
  value->next = *start;
  *start = value;
}
int pop(struct Node **start, int *val) {
  struct Node *del;
  if (is_empty(start))
    return 0;
  *val = (*start)->val;
  del = *start;
  *start = (*start)->next;
  free(del);
  return 1;
}
int peek(struct Node **start, int *val) {
  if (is_empty(start))
    return 0;
  *val = (*start)->val;
  return 1;
}
void display(struct Node *start) {
  struct Node *it;
  printf("{");
  if (!is_empty(&start)) {
    for (it = start; it->next != NULL; it = it->next)
      printf("%d,", it->val);
    printf("%d", it->val);
  }
  printf("}");
}
int main() {
  char ch;
  int tmp;
  struct Node *stack;

  init_stack(&stack);

  printf("\n1. Push");
  printf("\n2. Pop");
  printf("\n3. Peek");
  printf("\n4. Display");
  printf("\n5. Is Empty");
  printf("\n6. Exit\n");
  while (1) {
    puts(""); /* New line*/
    scanf(" %c", &ch);

    if (ch == '1') {
      printf("Add Data\t:");
      scanf("%d", &tmp);
      push(&stack, nodeFromValue(tmp));
    }
    if (ch == '2') {
      if (pop(&stack, &tmp))
        printf("Popped out : %d", tmp);
    }
    if (ch == '3') {
      if (peek(&stack, &tmp))
        printf("Peeked out : %d", tmp);
    }
    if (ch == '4') {
      printf("Data in Stack is\t:");
      display(stack);
    }
    if (ch == '5')
      printf((is_empty(&stack)) ? "Stack is Empty" : "Stack has values");
    if (ch == '6')
      return 0;
  }
}
/* OUTPUT
 * 1. Push
 * 2. Pop
 * 3. Peek
 * 4. Display
 * 5. Is Empty
 * 6. Exit
 * 1
 * Add Data        :23
 * 1
 * Add Data        :34
 * 1
 * Add Data        :45
 * 3
 * Peeked out : 45
 * 2
 * Popped out : 45
 * 4
 * Data in Stack is        :{34,23}
 * 5
 * Stack has values
 */