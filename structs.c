#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int		data;
	struct node 	*link;
} node;

int count_node(node *head)
{
	if(head == NULL)
		printf("no linked list");
	int counter;
	node *ptr = NULL;
	counter = 0;
	ptr = head;
	while (ptr != NULL)
	{
		counter++;
		ptr = ptr->link;
	}
	return counter;
}

int main()
{
	node *head = (node *)malloc(sizeof(node));
	head->data = 15;
	head->link = NULL;

	node *current = (node *)malloc(sizeof(node));
	current->data = 10;
	current->link = NULL;
	head->link = current;

	node *current2 = (node *)malloc(sizeof(node));
	current2->data = 20;
	current2->link = NULL;
	current->link = current2;
	head->link->link->data = 40;
	printf("%d", count_node(head));
}