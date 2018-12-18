/*
 * Program Title:- Double Ended Queue
 * Name:- Pratik Chowdhury
 * Roll Number:- 8322
 * Date of Performance:- 28.08.18
 */

# include<stdio.h>
# define MAX 5

int dequeue[MAX];
int left = -1, right = -1;

void insertright()
{
	int val;
	printf("\n Enter the value to be inserted\t");
	scanf("%d", &val);
	/* Queue Overflow*/
	if ((left == 0 && right == MAX - 1) || (left == right + 1))
	{
		printf("\n overflow");
		return;
	}
	else if (left == -1 && right == -1)//queue is empty
	{
		left = 0;
		right = 0;
	}
	else
	{
		if (right == MAX - 1)//end of the queue
			right = 0;
		else
			right = right + 1;
	}
	dequeue[right] = val;
}
void insertleft()
{
	int val;
	printf("\n Enter the value to be inserted\t");
	scanf("%d", &val);
	if ((left == 0 && right == MAX - 1) || (left == right + 1))//(if right=max-1 and left=0 then left==right+1)hence queue is full
	{
		printf("\n overflow");
		return;
	}
	else if (left == -1 && right == -1)//queue is empty
	{
		left = 0;
		right = 0;
	}
	else
	{
		if (left == 0)
			left = MAX - 1;
		else
			left = left - 1;
	}
	dequeue[left] = val;//value inserted from the left
}
void deleteleft()
{
	if (left == -1 && right == -1)
	{
		printf("\n underflow");
		return;
	}
	if (left == right)
	{
		int x = dequeue[left];
		printf("The value deleted is\t%d", x);
		left = -1;
		right = -1;
	}
	else
	{
		if (left == MAX - 1)//last element is deleted
		{
			printf("The value deleted is\t%d", dequeue[left]);
			left = 0;
		}
		else
		{
			printf("the value deleted is\t%d", dequeue[left]);
			left = left + 1;
		}

	}
}
void deleteright()
{
	if (left == -1 && right == -1)
	{
		printf("\n underflow");
		return;
	}
	if (left == right)
	{
		int x = dequeue[right];
		printf("The value deleted is\t%d", x);
		left = -1;
		right = -1;
	}
	else
	{
		if (right == 0)
			right = MAX - 1;
		else
			printf("The value deleted is\t%d", dequeue[right]);
		right = right - 1;
	}
}
void display()
{
	printf("\nleft=%d\tright=%d\n", left, right);
	int front = left, rear = right;
	if (front == -1 && rear == -1)
		printf("queue is empty");
	else if (front <= rear)
	{
		while (front <= rear)
		{
			printf("%d\t", dequeue[front]);
			front++;
		}
	}
	else
	{
		while (front <= MAX - 1)
		{
			printf("%d\t", dequeue[front]);
			front++;
		}
		front = 0;
		while (front <= rear)
		{
			printf("%d\t", dequeue[front]);
			front++;
		}
	}
}
void inputqueue()
{
	int option;
	printf("\n Input restricted queue");
	printf("\n 1.Insert right\n 2.Delete right\n 3.Delete left\n 4.Display\n 5.Exit\n");
	do
	{
		scanf("%d", &option);
		switch (option)
		{
			case 1:insertright();
				break;
			case 2:deleteright();
				break;
			case 3:deleteleft();
				break;
			case 4:display();
				break;
		}
	} while (option != 5);
}
void outqueue()
{
	int option;
	printf("\n Output Restricted Queue");
	printf("\n 1.Insert right\n 2.Insert left\n 3.Delete left\n 4.Display\n 5.Exit\n");
	do
	{
		scanf("%d", &option);
		switch (option)
		{
			case 1:insertright();
				break;
			case 2:insertleft();
				break;
			case 3:deleteleft();
				break;
			case 4:display();
				break;
		}
	} while (option != 5);
}
int main()
{
	int option;
	printf("\n 1.Input Queue");
	printf("\n 2.Output Queue\n");
	scanf("%d", &option);
	if (option == 1)
		inputqueue();
	else if (option == 2)
		outqueue();
	else
		printf("\nInvalid Option");
	return 0;
}

/*
 *1.Input Queue
 *2.Output Queue
 *1
 * Input restricted queue
 *1.Insert right
 *2.Delete right
 *3.Delete left
 *4.Display
 *5.Exit
 *1
 *Enter the value to be inserted 22
 *1
 *Enter the value to be inserted 34
 *1
 *Enter the value to be inserted 45
 *4
 *left=0  right=2
 *22      34      45
 *2
 *the value deleted is    45
 *3
 *the value deleted is    22
 *5
 *1.Input Queue
 *2.Output Queue
 *2
 *Output Restricted Queue
 *1.Insert right
 *2.Insert left
 *3.Delete left
 *4.Display
 *5.Exit
 *1
 *Enter the value to be inserted 23
 *1
 *Enter the value to be inserted 34
 *4
 *left=0  right=1
 *23      34
 *3
 *The value deleted is    23
*/