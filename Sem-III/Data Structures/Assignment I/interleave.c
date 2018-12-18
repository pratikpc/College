// Roll No:- 8322
// Name:-	 Pratik Chowdhury
// Title:- Interleave elements of a Queue

#include <stdio.h>

#define SIZE 20

struct Queue {
  int front;
  int rear;
  int a[SIZE];
};

void init_stack(struct Queue *p) { p->rear = p->front = -1; }

void enque(struct Queue *p, int x) {
  if (p->rear == SIZE - 1) {
    printf("overflow \n ");
    return;
  } else if (p->rear == -1 && p->front == -1) {
    p->front = 0;
  }
  p->a[++p->rear] = x;
}
int deque(struct Queue *p) {
  int x;
  if (p->rear == -1 && p->front == -1) {
    printf("UNDERFLOW \n");
    return 0;
  } else if (p->rear == p->front) {
    x = p->a[p->front];
    p->front = p->rear = -1;
    return x;
  } else {
    return p->a[p->front++];
  }
}
void display(struct Queue *p) {
  int i;
  for (i = p->front; i <= p->rear; i++)
    printf(" %d ", p->a[i]);
}
void interleave(struct Queue *ori, int n) {
  int i;

  struct Queue first, sec;
  init_stack(&first);
  init_stack(&sec);

  for (i = 0; i < n; i++)
    if (i < n / 2)
      enque(&first, deque(ori));
    else
      enque(&sec, deque(ori));

  for (i = 0; i < n / 2; i++) {
    enque(ori, deque(&first));
    enque(ori, deque(&sec));
  }
}
int main() {
  struct Queue ori;
  int tmp, i, n;

  printf("Enter even length of numbers: ");
  scanf("%d", &n);

  init_stack(&ori);

  for (i = 0; i < n; i++) {
    scanf("%d", &tmp);
    enque(&ori, tmp);
  }

  interleave(&ori, n);
  printf("the interleaved queue is \n");
  display(&ori);
  return 0;
}

// OUTPUT
// Enter even length of numbers: 4
// 1 2 3 4
// the interleaved queue is 1 3 2 4
// Enter even length of numbers : 10
// 11 12 13 14 15 16 17 18 19 20
// the interleaved queue is 11 16 12 17 13 18 14 19 15 20