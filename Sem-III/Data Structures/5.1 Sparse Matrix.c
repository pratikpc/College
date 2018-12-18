/*
 * Program Title:- Sparse Matrix using Linked List
 * Name:- Pratik Chowdhury
 * Roll Number:- 8322
 * Date of Performance:- 04.09.18
 */
#include <stdio.h>
#include <stdlib.h>
struct Node {
	int row, col, info;
	struct Node *next;
};
void addnode(struct Node **START, struct Node *newnode) {
	struct Node *ptr;
	if (START == NULL || *START == NULL)
		*START = newnode;
	else {
		for (ptr = *START; ptr->next != NULL; ptr = ptr->next);
		ptr->next = newnode;
		ptr = ptr->next;
	}
}
void entMatrix(struct Node **START, int dimr, int dimc) {
	int n, val, r, c, i = 0;
	struct Node *newnode;
	printf("Enter number of non zero terms in matrix\t");
	scanf("%d", &n);

	while (i < n) {
		printf("Enter value,row and column\n");
		scanf("%d,%d,%d", &val, &r, &c);
		if (r >= dimr || c >= dimc) {
			printf("Enter row and column values within dimensions");
			continue;
		}
		newnode = (struct Node *)malloc(sizeof(struct Node));
		newnode->info = val;
		newnode->row = r;
		newnode->col = c;
		newnode->next = NULL;
		addnode(START, newnode);
		i++;
	}
}
void display(struct Node *START, int dimr, int dimc) {
	struct Node *ptr;
	int i, j;

	if (START == NULL) return;
	ptr = START;
	for (i = 0; i < dimr; i++) {
		printf("\n");
		for (j = 0; j < dimc; j++) {
			if (ptr != NULL && ptr->row == i && ptr->col == j) {
				printf("\t%d", ptr->info);
				ptr = ptr->next;
			}
			else
				printf("\t0");
		}
	}
}
int main() {
	int option, dimr, dimc;
	struct Node *START = NULL;
	while (1) {
		printf("\n1.Enter Matrix\n2.Display Matrix\n3.Exit\n");
		scanf("%d", &option);
		switch (option) {
		case 1:
			printf("Enter dimensions(row, col) of the matrix\n");
			scanf("%d,%d", &dimr, &dimc);
			entMatrix(&START, dimr, dimc);
			break;
		case 2:
			display(START, dimr, dimc);
			break;
		case 3:
			return 0;
		}
	}
	return 0;
}
/*
 * OUTPUT
 * 1.Enter Matrix
 * 2.Display Matrix
 * 3.Exit
 * 1
 * Enter dimensions(row, col) of the matrix
 * 3,3
 * Enter number of non zero terms in matrix	3
 * Enter value,row and column
 * 12,0,0
 * Enter value,row and column
 * 23,0,2
 * Enter value,row and column
 * 3344,1,2
 * 2
 * 12	0	23
 * 0	0	3344
 * 0	0	0
 */
