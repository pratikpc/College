/*
 * Program Title:- Circular Linked List
 * Name:- Pratik Chowdhury
 * Roll Number:- 8322
 * Date of Performance:- 21.08.18
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int val;
  struct Node* next;
} Node;
struct Node* nodeFromValue(const int x) {
  struct Node* value = (struct Node*)malloc(sizeof(struct Node));
  value->val = x;
  value->next = NULL;
  return value;
}
void init_list(struct Node** start) {*start = NULL;}
int is_empty(Node** START) { return (START == NULL || *START == NULL);}
int insert_begin(Node** START, Node* value) {
  struct Node* it;
  if (is_empty(&value))
    return 0;
  if (is_empty(START)) {
    value->next = value;
    *START = value;
  } else {
    value->next = *START;
    for (it = *START; it->next != *START; it = it->next);
    *START = value;
    it->next = *START;
  }
  return 1;
}
int delete_begin(Node** START, int* val) {
  Node* tmp;
  Node* it;
  if (is_empty(START))
    return 0;
  else if (*START == (*START)->next) {
    *val = (*START)->val;
    tmp = *START;
    free(tmp);
    *START = NULL;
  } else {
    *val = (*START)->val;
    tmp = *START;
    for (it = *START; it->next != *START; it = it->next);
    it->next = (*START)->next;
    (*START) = (*START)->next;
    free(tmp);
  }
  return 1;
}
int insert_end(Node** START, Node* value) {
  Node* it;
  if (is_empty(START))
    return insert_begin(START, value);
  for (it = *START; it->next != *START; it = it->next);
  value->next = *START;
  it->next = value;
  it = it->next;
  return 1;
}
int delete_end(Node** START, int* val) {
  Node *it, *del;
  if (is_empty(START) || *START == (*START)->next)
    return delete_begin(START, val);
  for (it = *START; it->next->next != *START; it = it->next);
  del = it->next;
  *val = del->val;
  it->next = it->next->next;
  free(del);
  return 1;
}

void display(Node** START) {
  Node* it;
  printf("{");
  if (!is_empty(START)) {
    for (it = *START; it->next != *START; it = it->next)
      printf("%d,", it->val);
    printf("%d", it->val);
  }
  printf("}\n");
}
int insert_after(struct Node** start, int find_val, struct Node* value) {
  struct Node* it;
  if (is_empty(start))
    return 0;
  if ((*start)->val == find_val) {
    value->next = (*start)->next;
    (*start)->next = value;
  }
  for (it = (*start)->next; it != *start; it = it->next)
    if (it->val == find_val) {
      value->next = it->next;
      it->next = value;
      return 1;
    }
  return 0;
}
int delete_after(struct Node** start, int find_val, int* val) {
  struct Node* it;
  struct Node* del;
  if (is_empty(start) || *start == (*start)->next && (*start)->val == find_val)
    return 0;

  for (it = (*start); it->next != *start; it = it->next)
    if (it->val == find_val) {
      del = it->next;
      if (del != *start) {
        it->next = it->next->next;
        *val = del->val;
        free(del);
        del = NULL;
        return 1;
      }
    }
  return 0;
}
int find(struct Node* start, const int find) {
  struct Node* it;
  if (is_empty(&start))
    return 0;
  if (start->val == find)
    return 1;
  for (it = start; it->next != start; it = it->next)
    if (it->val == find)
      return 1; /* If found return true*/
  return 0;
}
int insert_before(Node** START, int find_val, Node* value) {
  struct Node* it;
  if (is_empty(&value))
    return 0;
  if (is_empty(START) || (*START)->val == find_val)
    return insert_begin(START, value);
  for (it = (*START); it->next != *START; it = it->next)
    if (it->next->val == find_val) {
      value->next = it->next;
      it->next = value;
      it = it->next;
      return 1;
    }
  return 0;
}

int main() {
  struct Node* START;
  int ch;
  int tmp1, tmp2;
  init_list(&START);

  puts("\n1. Insert Node at Beginining");
  puts("2. Insert Node at End");
  puts("3. Insert Node after Other");
  puts("4. Insert Node before Other");
  puts("5. Delete Node at Beginining");
  puts("6. Delete Node at End");
  puts("7. Delete Node after Other");
  puts("8. Display");
  puts("9. Find");
  puts("10. Exit");
  while (1) {
    scanf("%d", &ch);
    switch (ch) {
      case 1:
        printf("Enter the value of Node to be inserted at begin\t:");
        scanf("%d", &tmp1);
        insert_begin(&START, nodeFromValue(tmp1));
        break;
      case 2:
        printf("Enter the value of Node to be inserted at end\t:");
        scanf("%d", &tmp1);
        insert_end(&START, nodeFromValue(tmp1));
        break;
      case 3:
        printf("Enter After Which Element to Insert Node\t:");
        scanf("%d", &tmp1);
        printf("Enter the value of Node to be inserted after %d\t:", tmp1);
        scanf("%d", &tmp2);
        insert_after(&START, tmp1, nodeFromValue(tmp2));
        break;
      case 4:
        printf("Enter Before Which Element to Insert Node\t:");
        scanf("%d", &tmp1);
        printf("Enter the value of Node to be inserted before %d\t:", tmp1);
        scanf("%d", &tmp2);
        insert_before(&START, tmp1, nodeFromValue(tmp2));
        break;
      case 5:
        if (delete_begin(&START, &tmp1))
          printf("Deleted %d", tmp1);
        else
          printf("Unable to Delete Element");
        break;
      case 6:
        if (delete_end(&START, &tmp1))
          printf("Deleted %d", tmp1);
        else
          printf("Unable to Delete Element");
        break;
      case 7:
        printf("Enter After Which Element to Delete Node \t:");
        scanf("%d", &tmp1);
        if (delete_after(&START, tmp1, &tmp2))
          printf("Deleted %d", tmp2);
        else
          printf("Unable to Delete Element");
        break;
      case 8:
        display(&START);
        break;
      case 9:
        printf("Enter Which Element to Find\t:");
        scanf("%d", &tmp1);
        if (find(START, tmp1))
          printf("\nNode Found");
        else
          printf("Unable to Find Element");
        break;
      case 10:
        return 0;
    }
  }
  return 0;
}
/* OUTPUT
 * 1. Insert Node at Beginining
 * 2. Insert Node at End
 * 3. Insert Node after Other
 * 4. Insert Node before Other
 * 5. Delete Node at Beginining
 * 6. Delete Node at End
 * 7. Delete Node after Other
 * 8. Display
 * 9. Find
 * 10. Exit
 * 1
 * Enter the value of Node to be inserted at begin	:11
 * 2
 * Enter the value of Node to be inserted at end	:12
 * 3
 * Enter After Which Element to Insert Node	:11
 * Enter the value of Node to be inserted after 11	:45
 * 4
 * Enter Before Which Element to Insert Node	:45
 * Enter the value of Node to be inserted before 45	:78
 * 8
 * {11,78,45,12}
 * 5
 * Deleted 11
 * 6
 * Deleted 12
 * 7
 * Enter After Which Element to Delete Node 	:78
 * Deleted 45
 * 8
 * {78}
 * 9
 * Enter Which Element to Find	:78
 * Node Found
 */
