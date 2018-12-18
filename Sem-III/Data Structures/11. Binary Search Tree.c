#include <stdio.h>
#include <stdlib.h>

struct Tree	{
	int val;
	struct Tree* left;
	struct Tree* right;
};

struct Tree* nodeFromVal(int val)	{
	struct Tree* tree = (struct Tree*)(malloc(sizeof(struct Tree)));
	tree->left = tree->right = NULL;
	tree->val = val;
	return tree;
}
int is_empty(struct Tree** tree){return tree == NULL || *tree == NULL;}
void init_list(struct Tree** tree){*tree=NULL;}
void insert(struct Tree** root, struct Tree* newval)	{
	if(is_empty(root))
		*root = newval;
	if((*root)->val > newval->val)
	{
		if((*root)->left != NULL)
			return insert(&(*root)->left, newval);
		else
			(*root)->left = newval;
	}
	else if((*root)->val < newval->val)
	{
		if((*root)->right != NULL)
			return insert(&(*root)->right, newval);
		else
			(*root)->right = newval;
	}
}
void inorder(struct Tree** tree)
{
	if(is_empty(tree))
		return;
	inorder(&((*tree)->left));
	printf("%d,",(*tree)->val);
	inorder(&((*tree)->right));
}
void preorder(struct Tree** tree)
{
	if(is_empty(tree))
		return;
	printf("%d,",(*tree)->val);
	preorder(&((*tree)->left));
	preorder(&((*tree)->right));
}
void postrder(struct Tree** tree)
{
	if(is_empty(tree))
		return;
	postrder(&((*tree)->left));
	postrder(&((*tree)->right));
	printf("%d,",(*tree)->val);
}
int search(struct Tree** root, const int val)
{
	if(is_empty(root))
		return 0;
	if((*root)->val > val)
		return search(&(*root)->left, val);
	else if((*root)->val < val)
		return search(&(*root)->right, val);
	else if((*root)->val == val)
		return 1;
	return 0;
}

int count_all(struct Tree** root)
{
	if(is_empty(root))
		return 0;
	return count_all(&(*root)->left) + count_all(&(*root)->right) + 1;
}
int count_leaf(struct Tree** root)
{
	if(is_empty(root))
		return 0;
	else if((*root)->left == NULL && (*root)->right == NULL)
		return 1;
	else
		return count_leaf(&(*root)->left) + count_leaf(&(*root)->right);
}
int count_non_leaf(struct Tree** root)
{
	return count_all(root) - count_leaf(root);
}

int minVal(struct Tree** root)
{
	if(is_empty(root))
		return -1;
	while (*root != NULL && (*root)->left != NULL)
		*root = (*root)->left;
	return (*root)->val;
}
int maxVal(struct Tree** root)
{
	if(is_empty(root))
		return -1;
	while (*root != NULL && (*root)->right != NULL)
	{
		*root = (*root)->right;
	}
	return (*root)->val;
}

struct Tree* delete_node(struct Tree** root, const int key)
{
	struct Tree *temp;
	if (is_empty(root)) return 0; 
 	if (key < (*root)->val)
 		(*root)->left = delete_node(&(*root)->left, key);
 	else if (key > (*root)->val)
		(*root)->right = delete_node(&(*root)->right, key);
 	else
	{
		if ((*root)->left == NULL)
		{
			temp = (*root)->right;
			free(*root);
			*root = temp;
			return *root;
		}
		else if ((*root)->right == NULL)
		{
			temp = (*root)->left;
			free(*root);
			*root = temp;
			return *root;
		}
		for(temp = (*root)->right; temp->left != NULL; temp = temp->left);
		(*root)->val = temp->val;
 		(*root)->right = delete_node(&(*root)->right, temp->val);
	}
 		return NULL;
}

int main()
{
	struct Tree* root;
	init_list(&root);
	
	int opt, x;
	
	printf("Enter\n 1 to INSERT\n 2 to DELETE\n 3 to SEARCH\n 4 to Traverse INORDER\n 5 to Traverse PREORDER\n 6 to Traverse POSTORDER\n 7 to MIN\n 8 to MAX\n 9 to EXIT\n");
	
	while(1)
	{
		printf("Option = ");
		scanf("%d", &opt);
				
		switch(opt)
		{
			case 1: printf("Enter a value to insert:\n");
					scanf("%d", &x);
					insert(&root, nodeFromVal(x));
					printf("\nInorder traversal of the modified tree:\n");
					inorder(&root);
					break;
			
			case 2:	printf("Enter a value to delete:\n");
					scanf("%d", &x);
					deleteNode(&root, x);
					break;
			
			case 3:	printf("Enter a value to search:\n");
					scanf("%d", &x);
					if(search(&root, x))
						printf("Found\n");
					else
						printf("Not Found\n");
					break;
			
			case 4:	printf("\nInorder traversal of the tree:\n");
					inorder(&root);
					break;
			
			case 5: printf("\nPreorder traversal of the tree:\n");
					preorder(&root);
					break;
			
			case 6: printf("\nPostorder traversal of the tree:\n");
					postorder(&root);
					break;
			
			case 7:	printf("Minimum Element is: %d",minVal(&root));
					break;
			
			case 8: printf("Maximum Element is: %d",maxVal(&root));
					break;
			
			case 9: return -1;
		}
	}


	return 0;
}
