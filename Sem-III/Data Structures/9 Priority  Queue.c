/*
 * Program Title:- Priority Queue
 * Name:- Pratik Chowdhury
 * Roll Number:- 8322
 * Date of Performance:- 28.08.18
 */

#include <stdio.h>
#include <stdlib.h>

struct Node {
  int priority;
  int val;
  struct Node *next;
};
int is_empty(struct Node **list) { return *list == NULL; }
void init_list(struct Node **start) { *start = NULL; }
struct Node *nodeFromValue(const int priority, const int val) {
  struct Node *value = (struct Node *)malloc(sizeof(struct Node));
  value->val = val;
  value->priority = priority;
  value->next = NULL;
  return value;
}
int insert_begin(struct Node **start, struct Node *value) {
  if (is_empty(&value))
    return 0;
  value->next = *start;
  *start = value;
  return 1;
}
int enqueue(struct Node **START, struct Node *value) {
  struct Node *it;
  if (is_empty(&value))
    return 0;
  if (is_empty(START) || (*START)->priority > value->priority)
    return insert_begin(START, value);
  for (it = *START; it->next != NULL; it = it->next)
    if (it->next->priority > value->priority)
      break;
  value->next = it->next;
  it->next = value;
  it = it->next;
  return 1;
}
int dequeue(struct Node **start, int *val) {
  struct Node *del;
  if (is_empty(start))
    return 0;
  *val = (*start)->val;
  del = *start;
  *start = (*start)->next;
  free(del);
  return 1;
}
void display(struct Node **START) {
  struct Node *it;
  printf("{Priority, Value} = {");
  if (!is_empty(START)) {
    for (it = *START; it->next != NULL; it = it->next)
      printf("{%d:%d},", it->priority, it->val);
    printf("{%d:%d}", it->priority, it->val);
  }
  printf("}");
}
int main() {
  struct Node *queue;
  int ch, tmp1, tmp2;

  init_list(&queue);

  puts("\n1. Enqueue");
  puts("2. Deque");
  puts("3. Display");
  puts("4. Is Empty");
  puts("5. Exit");
  while (1) {
    scanf("%d", &ch);
    if (ch == 1) {
      printf("Add Data\nSet Priority\t:");
      scanf("%d", &tmp1);
      printf("Set Value\t:");
      scanf("%d", &tmp2);
      enqueue(&queue, nodeFromValue(tmp1, tmp2));
    }
    if (ch == 2)
      if (dequeue(&queue, &tmp1))
        printf("Dequed out : %d\n", tmp1);
      else
        puts("\nError Deleting. Queue Empty");
    if (ch == 3)
      display(&queue);
    if (ch == 4)
      puts((is_empty(&queue) ? "Queue is Empty" : "Queue has values"));
    if (ch == 5)
      return 0;
  }
  return 0;
}
/*
 * OUTPUT
 * 1. Enqueue
 * 2. Deque
 * 3. Display
 * 4. Is Empty
 * 5. Exit
 * 1
 * Add Data
 * Set Priority    :1
 * Set Value       :12
 * 1
 * Add Data
 * Set Priority    :5
 * Set Value       :46
 * 1
 * Add Data
 * Set Priority    :3
 * Set Value       :78
 * 3
 * {Priority, Value} = {{1:12},{3:78},{5:46}}
 * 2
 * Dequed out : 12
 * 4
 * Queue has values
 * 5
 */