/*
 * Program Title:- Singly Linked List
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
void init_list(struct Node **start) { *start = NULL; }
struct Node *nodeFromValue(const int x) {
  struct Node *value = (struct Node *)malloc(sizeof(struct Node));
  value->val = x;
  value->next = NULL;
  return value;
}
void insert_begin(struct Node **start, struct Node *value) {
  if (is_empty(&value))
    return;
  value->next = *start;
  *start = value;
}
void insert_end(struct Node **start, struct Node *value) {
  struct Node *it;
  if (is_empty(start))
    return insert_begin(start, value);
  for (it = *start; it->next != NULL; it = it->next)
    ;
  it->next = value;
  it = value;
}
int insert_after(struct Node **start, int find_val, struct Node *value) {
  struct Node *it;
  if (is_empty(start)) {
    insert_begin(start, value);
    return 1;
  }
  for (it = *start; it != NULL; it = it->next)
    if (it->val == find_val) {
      value->next = it->next;
      it->next = value;
      return 1;
    }
  return 0;
}
int insert_before(struct Node **start, int find_val, struct Node *value) {
  struct Node *it;
  if (is_empty(start)) {
    insert_begin(start, value);
    return 1;
  }
  for (it = *start; it->next != NULL; it = it->next)
    if (it->next->val == find_val) {
      value->next = it->next;
      it->next = value;
      return 1;
    }
  return 0;
}
int delete_begin(struct Node **start, int *val) {
  struct Node *del;
  if (is_empty(start))
    return 0;
  *val = (*start)->val;
  del = *start;
  *start = (*start)->next;
  free(del);
  return 1;
}
int delete_end(struct Node **start, int *val) {
  struct Node *it;
  struct Node *del;
  if (is_empty(start))
    return 0;
  if (is_empty(&((*start)->next))) {
    del = *start;
    free(del);
    *start = NULL;
    return 1;
  }
  for (it = *start; it->next->next != NULL; it = it->next)
    ;
  del = it->next;
  *val = del->val;
  it->next = NULL;
  free(del);
  return 1;
}
int delete_after(struct Node **start, int find_val, int *val) {
  struct Node *it;
  struct Node *del;
  if (is_empty(start))
    return 0;
  for (it = *start; it != NULL; it = it->next)
    if (it->val == find_val) {
      del = it->next;
      if (del != NULL) {
        it->next = it->next->next;
        *val = del->val;
        free(del);
        del = NULL;
      }
      return 1;
    }
  return 0;
}
int delete_specific_node(struct Node **start, int find_val) {
  struct Node *it, *del;
  int tmp;
  while (1)
    if (is_empty(start))
      return 0;
    else if ((*start)->val == find_val)
      delete_begin(start, &tmp);
    else
      break;
  for (it = *start; it->next != NULL; it = it->next)
    if (it->next->val == find_val) {
      del = it->next;
      if (del != NULL) {
        it->next = it->next->next;
        free(del);
        del = NULL;
      }
      return 1;
    }
  return 0;
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
void swap(struct Node **a, struct Node **b) {
  int tmp = (*a)->val;
  (*a)->val = (*b)->val;
  (*b)->val = tmp;
}
void sort(struct Node **start) {
  struct Node *i, *j;
  if (!is_empty(start))
    for (i = *start; i->next != NULL; i = i->next)
      for (j = i; j->next != NULL; j = j->next)
        if (j->val > j->next->val)
          swap(&j, (&j->next));
}
int find(struct Node *start, const int find) {
  struct Node *it;
  for (it = start; it != NULL; it = it->next)
    if (it->val == find)
      return 1; /* If found return true*/
  return 0;
}
int count(struct Node *start) {
  struct Node *it;
  int count = 0;
  for (it = start; it != NULL; it = it->next)
    ++count;
  return count;
}
void reverse(struct Node **start) {
  int i, size = count(*start), val;
  struct Node *tmp = NULL;
  for (i = 0; i < size; ++i) {
    delete_begin(start, &val);
    insert_begin(&tmp, nodeFromValue(val));
  }
  for (i = 0; i < size; ++i) {
    delete_begin(&tmp, &val);
    insert_end(start, nodeFromValue(val));
  }
}

int main() {
  struct Node *START;
  int ch;
  int tmp1, tmp2;
  init_list(&START);

  while (1) {
    puts("\n1. Insert Node at Beginining");
    puts("2. Insert Node at End");
    puts("3. Insert Node after Other");
    puts("4. Insert Node before Other");
    puts("5. Delete Node at Beginining");
    puts("6. Delete Node at End");
    puts("7. Delete Node after Other");
    puts("8. Delete Specific Node");
    puts("9. Display");
    puts("10. Sort");
    puts("11. Find");
    puts("12. Count");
    puts("13. Reverse");
    puts("14. Exit");
    scanf("%d", &ch);
    switch (ch) {
    case 1:
      printf("\nEnter the value of Node to be inserted at begin\t:");
      scanf("%d", &tmp1);
      insert_begin(&START, nodeFromValue(tmp1));
      break;
    case 2:
      printf("\nEnter the value of Node to be inserted at end\t:");
      scanf("%d", &tmp1);
      insert_end(&START, nodeFromValue(tmp1));
      break;
    case 3:
      printf("\nEnter After Which Element to Insert Node\t:");
      scanf("%d", &tmp1);
      printf("\nEnter the value of Node to be inserted after %d\t:", tmp1);
      scanf("%d", &tmp2);
      insert_after(&START, tmp1, nodeFromValue(tmp2));
      break;
    case 4:
      printf("\nEnter Before Which Element to Insert Node\t:");
      scanf("%d", &tmp1);
      printf("\nEnter the value of Node to be inserted before %d\t:", tmp1);
      scanf("%d", &tmp2);
      insert_before(&START, tmp1, nodeFromValue(tmp2));
      break;
    case 5:
      if (delete_begin(&START, &tmp1))
        printf("\nDeleted %d", tmp1);
      else
        printf("\nUnable to Delete Element");
      break;
    case 6:
      if (delete_end(&START, &tmp1))
        printf("\nDeleted %d", tmp1);
      else
        printf("\nUnable to Delete Element");
      break;
    case 7:
      printf("\nEnter After Which Element to Delete Node \t:");
      scanf("%d", &tmp1);
      if (delete_after(&START, tmp1, &tmp2))
        printf("\nDeleted %d", tmp2);
      else
        printf("\nUnable to Delete Element");
      break;
    case 8:
      printf("\nEnter Which Element to Delete\t:");
      scanf("%d", &tmp1);
      if (delete_specific_node(&START, tmp1))
        printf("\nNode Deleted");
      else
        printf("\nUnable to Delete Element");
      break;
    case 9:
      display(START);
      break;
    case 10:
      sort(&START);
      break;
    case 11:
      printf("\nEnter Which Element to Find\t:");
      scanf("%d", &tmp1);
      if (find(START, tmp1))
        printf("\nNode Found");
      else
        printf("\nUnable to Find Element");
      break;
    case 12:
      printf("\nThe Number of Elements are %d", count(START));
      break;
    case 13:
      reverse(&START);
      break;
    case 14:
      return 0;
    }
  }
}
/*	OUTPUT
 *	1. Insert Node at Beginining
 *	2. Insert Node at End
 *	3. Insert Node after Other
 *	4. Insert Node before Other
 *	5. Delete Node at Beginining
 *	6. Delete Node at End
 *	7. Delete Node after Other
 *	8. Delete Specific Node
 *	9. Display
 *	10. Sort
 *	11. Find
 *	12. Exit
 *	1
 *	Enter the value of Node to be inserted at begin	:23
 *	2
 *	Enter the value of Node to be inserted at end	:34
 *	3
 *	Enter After Which Element to Insert Node	:34
 *	Enter the value of Node to be inserted after 34	:499
 *	4
 *	Enter Before Which Element to Insert Node	:34
 *	Enter the value of Node to be inserted before 34	:22
 *	9
 *	{23,22,34,499}
 *	5
 *	Deleted 23
 *	6
 *	Deleted 499
 *	9
 *	{22,34}
 *	1
 *	Enter the value of Node to be inserted at begin	:44
 *	9
 *	{44,22,34}
 *	10
 *	9
 *	{22,34,44}
 *	11
 *	Enter Which Element to Find	:22
 *	Node Found
 * 13
 * 9
 * {44,34,22}
 * 12
 * The Number of Elements are 3
 */
