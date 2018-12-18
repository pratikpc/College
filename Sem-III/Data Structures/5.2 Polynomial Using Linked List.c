/*
 * Program Title:- Polynomial using Linked List
 * Name:- Pratik Chowdhury
 * Roll Number:- 8322
 * Date of Performance:- 04.09.18
 */
#include <stdio.h>
#include <stdlib.h>
struct Node {
  int pow, coeff;
  struct Node *next;
};
int is_empty(struct Node **list) { return *list == NULL; }
void init_list(struct Node **start) { *start = NULL; }
void insert_begin(struct Node **start, struct Node *value) {
  if (is_empty(&value))
    return;
  value->next = *start;
  *start = value;
}
struct Node* nodeFromValue(const int pow, const int coeff)	{
      struct Node *newnode = (struct Node *)malloc(sizeof(struct Node));
      newnode->coeff = coeff;
      newnode->pow = pow;
      return newnode;
}
void addnode(struct Node** start, struct Node* value) {
  struct Node *it;
  if (is_empty(start))
    return insert_begin(start, value);
  for (it = *start; it->next != NULL; it = it->next);
  it->next = value;
  it = value;
}
void swap(struct Node **a, struct Node **b) {
  int pow = (*a)->pow;
  int coeff = (*a)->coeff;
  (*a)->pow = (*b)->pow;
  (*a)->coeff = (*b)->coeff;
  (*b)->pow = pow;
  (*b)->coeff = coeff;
}
void sort(struct Node **start) {
  struct Node *i, *j;
  if (!is_empty(start))
    for (i = *start; i->next != NULL; i = i->next)
      for (j = i; j->next != NULL; j = j->next)
        if (j->pow < j->next->pow)
          swap(&j, (&j->next));
}
void add(struct Node* START1, struct Node* START2,
                 struct Node** START3) {
  struct Node *ptr1, *ptr2;
  
  sort(&START1);
  sort(&START2);
  
  ptr1 = START1;
  ptr2 = START2;
  while (ptr1 != NULL && ptr2 != NULL) {
    if (ptr1->pow == ptr2->pow) {
      addnode(START3, nodeFromValue(ptr1->pow, ptr1->coeff + ptr2->coeff));
      ptr1 = ptr1->next;
      ptr2 = ptr2->next;
    } else if (ptr1->pow < ptr2->pow) {
      addnode(START3, nodeFromValue(ptr2->pow, ptr2->coeff));
      ptr2 = ptr2->next;
    } else {
      addnode(START3, nodeFromValue(ptr1->pow, ptr1->coeff));
      ptr1 = ptr1->next;
    }
  }
	while (ptr2 != NULL) {
      addnode(START3, nodeFromValue(ptr2->pow, ptr2->coeff));
      ptr2 = ptr2->next;
  }
	while (ptr1 != NULL) {
      addnode(START3, nodeFromValue(ptr1->pow, ptr1->coeff));
      ptr1 = ptr1->next;
    }
}
void display(struct Node *START) {
	struct Node *ptr;
	if (START == NULL) 
		return;
	printf("\n");
	ptr = START;
	while (ptr != NULL) {
		printf("%dx%d", ptr->coeff, ptr->pow);
      ptr = ptr->next;
      if (ptr == NULL)
        printf("=0");
      else if(ptr->coeff > 0)
        printf("+");
      else
        printf("-");
   }
}
int main() {
  struct Node *start1 = NULL;
  struct Node *start2 = NULL;
  struct Node *start3 = NULL;
  int n, co, power, i;
  printf("\nEnter first polynomial");
  printf("\nEnter number of terms\t:");
  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    printf("Enter coefficient\t:");
    scanf("%d", &co);
    printf("Enter power\t:");
    scanf("%d", &power);
    addnode(&start1, nodeFromValue(power, co));
  }
  printf("Enter second polynomial");
  printf("\nEnter number of terms\t:");
  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    printf("Enter coefficient\t:");
    scanf("%d", &co);
    printf("Enter power\t:");
    scanf("%d", &power);
    addnode(&start2, nodeFromValue(power, co));
  }
  printf("The entered polynomials are");
  display(start1);
  display(start2);
  add(start1, start2, &start3);
  printf("\nAdding the two polynomials");
  display(start3);
  
  return 0;
}
/*
 * Enter first polynomial
 * Enter number of terms	:2
 * Enter coefficient	:5
 * Enter power	:2
 * Enter coefficient	:10
 * Enter power	:0
 * Enter second polynomial
 * Enter number of terms	:3
 * Enter coefficient	:23
 * Enter power	:3
 * Enter coefficient	:10
 * Enter power	:2
 * Enter coefficient	:5
 * Enter power	:0
 * The entered polynomials are
 * 5x2+10x0=0
 * 23x3+10x2+5x0=0
 */
 * Adding the two polynomials
 * 23x3+15x2+15x0=0
 */
