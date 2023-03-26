#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	int x;
	int y;
	struct Node *next;
} Node;

typedef struct Stack
{
	Node *top;
} Stack;

void push(Stack *stack ,int x, int y)
{
	Node *newNode = malloc(sizeof(Node));
	if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
	newNode->x = x;
	newNode->y = y;
	newNode->next = stack->top;
	stack->top = newNode;
}

Stack *create_stack()
{
	Stack *stack = malloc(sizeof(Stack));
	stack->top = NULL;
	return stack;
}

int is_empty(Stack *stack)
{
	return (stack->top == NULL);
}
Node *pop(Stack *stack)
{
	if (is_empty(stack)) {
		printf("Stack Underflow\n");
		return NULL;
    }
	Node *temp = malloc(sizeof(Node));
	if (temp == NULL) {
    	printf("Memory allocation failed\n");
    	return NULL;
	}
	int x;
	int y;

	x = stack->top->x;
	y = stack->top->y;
	temp = stack->top;
	stack->top = stack->top->next;
	printf("popped [%d][%d]\n", temp->x, temp->y);
	return temp;
}

void peek(Stack *stack)
{
	if (is_empty(stack))
		printf("Stack is empty!\n");
	else
	{
		printf("top value is: [%d][%d]\n", stack->top->x, stack->top->y);
	}
}



int count_nodes(Stack *stack)
{
	int x;

	x = 0;
	Node *temp = stack->top;
	while(temp != NULL)
	{
		x++;
		temp = temp->next;
	}
	return x;
}

void display_stack(Stack *stack)
{
	if (is_empty(stack))
		printf("Stack is Empty!\n");
	else {
		Node *temp = malloc(sizeof(Node));
		temp = stack->top;
		while (temp != NULL)
		{
			printf("|[%d][%d]|\n", temp->x, temp->y);
			temp = temp->next;
		}
	}
}

int in_visited(Stack *visited, int a, int b)
{
	if (is_empty(visited))
		printf("Visited Stack is Empty!\n");
	else {
		Node *temp = malloc(sizeof(Node));
		temp = visited->top;
		while (temp != NULL)
		{
			if (a == temp->x && b == temp->y)
				return (1);
			temp = temp->next;
		}
	}	
	return (0);
}




void get_next_moves(Stack *s, int a, int b, char **map)
{
	if (a > 0 && map[a - 1][b] != '1')
		push(s, a - 1, b);
	if (b < 6 && map[a][b + 1] != '1' )
		push(s, a, b + 1);
	if (a < 5 && map[a + 1][b] != '1')
		push(s, a + 1, b);
	if (b > 0 && map[a][b - 1] != '1')
		push(s, a, b - 1);
}

int main ()
{
	Stack *s = create_stack();
	Stack *visited = create_stack();

	int start_x = 3;
	int start_y = 4;
	int exit_x = 1;
	int exit_y = 2;

	int x = 0;
	int y = 0;
	int exit_found = 0;
	char **map = malloc(6 * sizeof(char *));
	int c = 0;
	while (c < 6)
	{
		map[c] = malloc(7 * sizeof(char));
		c++;
	}
	map[0] = "111111";
	map[1] = "11E1C1";
	map[2] = "110111";
	map[3] = "1000P1";
	map[4] = "111111";
	map[5] = NULL;
	push(s, start_x, start_y);
	while (!is_empty(s))
	{
		Node *popped = pop(s);
		if (popped != NULL) {
    		x = popped->x;
    		y = popped->y;
		}
		if (in_visited(visited, x, y))
			continue;
		else
		{
			push(visited, x, y);
			if (in_visited(visited, exit_x, exit_y))
			{
				exit_found++;
				break;
			}
			printf("-----------------\n");
			get_next_moves(s, x, y, map);
		}
	}
	
	display_stack(s);
	printf("----------\n");
	display_stack(visited);
	printf("----------\n");
	if (exit_found)
		printf("path to E found!\n");
	else
		printf("path to E was not found!\n");
	free(s);
	free(visited);
	s = NULL;
	visited = NULL;
}