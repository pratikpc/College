// Roll No:- 8322
// Name:-	 Pratik Chowdhury
// Title:- Implement Stack Using Queue

#include <stdio.h>
#define MAX 20

struct Queue {
  int data[MAX];
  int front;
  int end;
};

int isEmpty(const struct Queue *const q) { return (q->front == q->end); }
int isFull(const struct Queue *const q) {
  return ((q->end + 1) % MAX == q->front || q->end == MAX);
}
int enqueue(struct Queue *q, const int val) {
  if (isFull(q))
    return 0;
  if (isEmpty(q))
    q->front = q->end = 0;

  q->data[q->end] = val;
  q->end = (q->end + 1) % MAX;

  return 1;
}
void init_queue(struct Queue *q) { q->front = q->end = -1; }
int dequeue(struct Queue *q, int *val) {
  if (isEmpty(q)) {
    init_queue(q);
    return 0;
  }
  *val = q->data[q->front];
  q->front = (q->front + 1) % MAX;
  return 1;
}
void display(struct Queue *q) {
  int i;
  printf("{");
  if (!isEmpty(q)) {
    printf("%d", q->data[q->front]);
    for (i = (q->front + 1) % MAX; i != q->end; i = (i + 1) % MAX)
      printf(",%d", q->data[i]);
  }
  printf("}");
}
int size(struct Queue *q) {
  int sz = 0;
  int tmp_val;

  struct Queue tmp_q;
  init_queue(&tmp_q);

  while (!isEmpty(q)) {
    dequeue(q, &tmp_val);
    enqueue(&tmp_q, tmp_val);
    ++sz;
  }
  while (!isEmpty(&tmp_q)) {
    dequeue(&tmp_q, &tmp_val);
    enqueue(q, tmp_val);
  }
  return sz;
}

int push_stack(struct Queue *q, int elem) { return enqueue(q, elem); }
int pop_stack(struct Queue *q, int *elem) {
  struct Queue tmp_q;
  int tmp_val;
  int sz;

  if (isEmpty(q))
    return 0;

  init_queue(&tmp_q);

  for (sz = size(q); sz > 1; --sz) {
    dequeue(q, &tmp_val);
    enqueue(&tmp_q, tmp_val);
  }
  if (!isEmpty(q))
    dequeue(q, elem);
  while (!isEmpty(&tmp_q)) {
    dequeue(&tmp_q, &tmp_val);
    enqueue(q, tmp_val);
  }

  return 1;
}
int peek_stack(struct Queue *q, int *elem) {
  struct Queue tmp_q;
  int tmp_val = 0;

  if (isEmpty(q))
    return 0;

  init_queue(&tmp_q);

  while (!isEmpty(q)) {
    dequeue(q, &tmp_val);
    enqueue(&tmp_q, tmp_val);
  }
  *elem = tmp_val;
  while (!isEmpty(&tmp_q)) {
    dequeue(&tmp_q, &tmp_val);
    enqueue(q, tmp_val);
  }

  return 1;
}

int main() {
  struct Queue stack;
  char ch;
  int tmp;

  init_queue(&stack);

  printf("\n1. Push");
  printf("\n2. Pop");
  printf("\n3. Peek");
  printf("\n4. Display");
  printf("\n5. Is Full");
  printf("\n6. Is Empty");
  printf("\n7. Exit\n");

  while (1) {
    scanf(" %c", &ch);

    if (ch == '1') {
      printf("\nAdd Data\t:");
      scanf("%d", &tmp);
      push_stack(&stack, tmp);
    }
    if (ch == '2')
      if (pop_stack(&stack, &tmp))
        printf("\nPopped out : %d", tmp);
    if (ch == '3')
      if (peek_stack(&stack, &tmp))
        printf("\nPeeped out : %d", tmp);
    if (ch == '4') {
      printf("\nData in Stack is\t:");
      display(&stack);
    }
    if (ch == '5')
      printf((isFull(&stack)) ? "\nStack is Full"
                              : "\nStack still has Space left");
    if (ch == '6')
      printf((isEmpty(&stack)) ? "\nStack is Empty" : "\nStack has values");
    if (ch == '7')
      return 0;
  }
}
// OUTPUT
// 1. Push
// 2. Pop
// 3. Peek
// 4. Display
// 5. Is Full
// 6. Is Empty
// 7. Exit
// 1
// Add Data : 45
// 1
// Add Data : 56
// 1
// Add Data : 67
// 3
// Peeped out : 67
// 2
// Popped out : 67
// 4
// Data in Stack is : 45,56,
// 5
// Stack still has Space left
// 6
// Stack has values
// 7