/*
 * Program Title:- Doubly Linked List
 * Name:- Pratik Chowdhury
 * Roll Number:- 8322
 * Date of Performance:- 27.08.18
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int val;
	struct Node* next;
	struct Node* prev;
} Node;
int is_empty(struct Node** list) { return list == NULL || *list == NULL; }
void init_list(struct Node** start) { *start = NULL; }
struct Node* nodeFromValue(const int x) {
	struct Node* value = (struct Node*)malloc(sizeof(struct Node));
	value->val = x;
	value->next = NULL;
	value->prev = NULL;
	return value;
}
int insert_begin(struct Node** START, struct Node* value) {
	if (is_empty(&value))
		return 0;
	if (is_empty(START))
		*START = value;
	else {
		(*START)->prev = value;
		value->next = *START;
		*START = value;
	}
	return 1;
}
int delete_begin(struct Node** START, int* value) {
	if (is_empty(START))
		return 0;
	*value = (*START)->val;
	*START = (*START)->next;
	if (!is_empty(START))
		(*START)->prev = NULL;
	return 1;
}
int insert_end(struct Node** START, struct Node* value) {
	Node* it;
	if (is_empty(&value))
		return 0;
	if (is_empty(START))
		return insert_begin(START, value);
	for (it = *START; it->next != NULL; it = it->next);
	it->next = value;
	value->prev = it;
	it = it->next;
	return 1;
}
int delete_end(struct Node** START, int* value) {
	Node* it, *del;
	if (is_empty(START))
		return 0;
	for (it = *START; it->next != NULL; it = it->next);
	del = it;
	*value = del->val;
	it = it->prev;
	it->next = NULL;
	free(del);
	return 1;
}
int insert_before(struct Node** START, int find, struct Node* value) {
	struct Node * it;
	if (is_empty(&value) || is_empty(START))
		return 0;
	if ((*START)->val == find)
		return insert_begin(START, value);
	for (it = *START; it != NULL; it = it->next) {
		if (it->val == find) {
			it = it->prev;
			it->next->prev = value;
			value->next = it->next;
			value->prev = it;
			it->next = value;
			it = it->next;
			return 1;
		}
	}
	return 0;
}
int delete_before(struct Node** START, int find, int* value) {
	struct Node* it;
	struct Node* del;
	if (is_empty(START) || (*START)->val == find)
		return 0;
	for (it = *START; it != NULL; it = it->next) {
		if (it->val == find) {
			del = it->prev;
			if (del == *START)
				return delete_begin(START, value);
			*value = del->val;
			it->prev = it->prev->prev;
			it->prev->next = it;
			free(del);
			return 1;
		}
	}
	return 9;
}
int insert_after(struct Node** START, int find, struct Node* value) {
	struct Node * it;
	if (is_empty(&value) || is_empty(START))
		return 0;
	if ((*START)->val == find)
		return insert_begin(START, value);
	for (it = *START; it != NULL; it = it->next) {
		if (it->val == find) {
			if (it->next == NULL)
				return insert_end(START, value);
			it->next->prev = value;
			value->next = it->next;
			value->prev = it;
			it->next = value;
			it = it->next;
			return 1;
		}
	}
	return 0;
}
int delete_after(struct Node** START, int find, int* value) {
	struct Node* it;
	struct Node* del;
	if (is_empty(START))
		return 0;
	for (it = *START; it->next != NULL; it = it->next) {
		if (it->val == find) {
			del = it->next;
			*value = del->val;
			it->next = it->next->next;
			if (it->next != NULL)
				it->next->prev = it;
			free(del);
			return 1;
		}
	}
	return 9;
}
void display(struct Node** start) {
	struct Node * it;
	printf("{");
	if (!is_empty(start)) {
		for (it = *start; it->next != NULL; it = it->next)
			printf("%d,", it->val);
		printf("%d", it->val);
	}
	printf("}\n");
}
int main() {
	struct Node* START;
	int ch, tmp1, tmp2;
	init_list(&START);
	puts("\n1. Insert Node at Beginining");
	puts("2. Insert Node at End");
	puts("3. Insert Node after Other");
	puts("4. Insert Node before Other");
	puts("5. Delete Node at Beginining");
	puts("6. Delete Node at End");
	puts("7. Delete Node after Other");
	puts("8. Delete Node before Other");
	puts("9. Display");
	puts("10. Exit");
	while (1) {
		scanf("%d", &ch);
		if (ch == 1) {
			printf("\nEnter the value of Node to be inserted at begin\t:");
			scanf("%d", &tmp1);
			insert_begin(&START, nodeFromValue(tmp1));
		}if (ch == 2) {
			printf("\nEnter the value of Node to be inserted at end\t:");
			scanf("%d", &tmp1);
			insert_end(&START, nodeFromValue(tmp1));
		}if (ch == 3) {
			printf("\nEnter After Which Element to Insert Node\t:");
			scanf("%d", &tmp1);
			printf("\nEnter the value of Node to be inserted after %d\t:", tmp1);
			scanf("%d", &tmp2);
			insert_after(&START, tmp1, nodeFromValue(tmp2));
			break;
		}if (ch == 4) {
			printf("\nEnter Before Which Element to Insert Node\t:");
			scanf("%d", &tmp1);
			printf("\nEnter the value of Node to be inserted before %d\t:", tmp1);
			scanf("%d", &tmp2);
			insert_before(&START, tmp1, nodeFromValue(tmp2));
		}if (ch == 5)
			if (delete_begin(&START, &tmp1))
				printf("\nDeleted %d", tmp1);
			else
				printf("\nUnable to Delete Element");
		if (ch == 6)
			if (delete_end(&START, &tmp1))
				printf("\nDeleted %d", tmp1);
			else
				printf("\nUnable to Delete Element");
		if (ch == 7) {
			printf("\nEnter After Which Element to Delete Node \t:");
			scanf("%d", &tmp1);
			if (delete_after(&START, tmp1, &tmp2))
				printf("\nDeleted %d", tmp2);
			else
				printf("\nUnable to Delete Element");
		}if (ch == 8) {
			printf("\nEnter Before Which Element to Delete Node \t:");
			scanf("%d", &tmp1);
			if (delete_before(&START, tmp1, &tmp2))
				printf("\nDeleted %d", tmp2);
			else
				printf("\nUnable to Delete Element");
		}
		if (ch == 9)
			display(&START);
		if (ch == 10)
			return 0;
	}
	return 0;
}
/* OUTPUT
 *	1. Insert Node at Beginining
 *	2. Insert Node at End
 *	3. Insert Node after Other
 *	4. Insert Node before Other
 *	5. Delete Node at Beginining
 *	6. Delete Node at End
 *	7. Delete Node after Other
 *	8. Delete Node before Other
 *	9. Display
 *	10. Exit
 *	1
 *	Enter the value of Node to be inserted at begin	:12
 *	2
 *	Enter the value of Node to be inserted at end	:13
 *	3
 *	Enter After Which Element to Insert Node	:12
 *	Enter the value of Node to be inserted after 12	:45
 *	4
 *	Enter Before Which Element to Insert Node	:45
 *	Enter the value of Node to be inserted before 45	:67
 *	9
 *	{67,45,12,13}
 *	5
 *	Deleted 67
 *	6
 *	Deleted 13
 *	7
 *	Enter After Which Element to Delete Node 	:45
 *	Deleted 12
 *	1
 *	Enter the value of Node to be inserted at begin	:100
 *	8
 *	Enter Before Which Element to Delete Node 	:45
 *	Deleted 100
 */
