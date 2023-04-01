/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 08:01:53 by rchahban          #+#    #+#             */
/*   Updated: 2023/04/01 02:41:13 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"
#include "../../get_next_line.h"

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
	return (stack);
}

int is_empty(Stack *stack)
{
	return (stack->top == NULL);
}

void get_next_moves(Stack *s, int a, int b, char **map, int rows, int cols, char goal)
{
	if (goal == EXIT)
	{
		if (a > 0 && map[a - 1][b] != WALL)
			push(s, a - 1, b);
		if (b < cols && map[a][b + 1] != WALL)
			push(s, a, b + 1);
		if (a < rows && map[a + 1][b] != WALL)
			push(s, a + 1, b);
		if (b > 0 && map[a][b - 1] != WALL)
			push(s, a, b - 1);
	}
	else
	{
		if (a > 0 && (map[a - 1][b] != WALL && map[a - 1][b] != EXIT))
			push(s, a - 1, b);
		if (b < cols && (map[a][b + 1] != WALL &&  map[a][b + 1] != EXIT))
			push(s, a, b + 1);
		if (a < rows && (map[a + 1][b] != WALL && map[a + 1][b] != EXIT))
			push(s, a + 1, b);
		if (b > 0 && (map[a][b - 1] != WALL && map[a][b - 1] != EXIT))
			push(s, a, b - 1);
	}
}

Node *pop(Stack *stack)
{
	int x;
	int y;

	if (is_empty(stack)) {
		return NULL;
    }
	Node *temp = malloc(sizeof(Node));
	if (temp == NULL) {
    	return NULL;
	}
	x = stack->top->x;
	y = stack->top->y;
	temp = stack->top;
	stack->top = stack->top->next;
	return (temp);
}

void display_stack(Stack *stack)
{
	int x;

	x = 0;
	if (is_empty(stack))
		printf("Stack is Empty!\n");
	else {
		Node *temp = malloc(sizeof(Node));
		temp = stack->top;
		while (temp != NULL)
		{
			printf("|[%d][%d]|\n", temp->x, temp->y);
			temp = temp->next;
			x++;
		}
	}
}

int in_visited(Stack *visited, int a, int b)
{
	if (is_empty(visited))
		return (0);
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

int count_collectibles(char **map)
{
	int	x;
	int	y;
	int	collectibles;

	x = 0;
	y = 0;
	collectibles = 0;
	while(map[x])
	{
		y = 0;
		while(map[x][y])
		{
			if (map[x][y] == COLLECTIBLE)
				collectibles++;
			y++;
		}
		x++;
	}
	return (collectibles);
}

void assign_point(char **map, int *start_x, int *start_y, int *exit_x, int *exit_y)
{
	int x;
	int y;
	
	x = 0;
	while(map[x] != NULL)
	{
		y = 0;
		while (map[x][y] != '\0')
		{
			if(map[x][y] == 'P')
			{
				*start_x = x;
				*start_y = y;
			}
			if(map[x][y] == 'E')
			{
				*exit_x = x;
				*exit_y = y;
			}
			y++;
		}
		x++;
	}
}

int	path_is_valid(char **map, int cols, int rows)
{
	Stack *s = create_stack();
	Stack *visited = create_stack();
	Stack *collectibles_stack = create_stack();

	assign_point(map, &(game.player_x), &(game.player_y), &(game.exit_x), &(game.exit_y));
	// Part 1: Exit detection
	if (map[game.exit_x + 1][game.exit_y] == WALL && map[game.exit_x - 1][game.exit_y] == WALL
		&& map[game.exit_x][game.exit_y + 1] == WALL && map[game.exit_x][game.exit_y - 1] == WALL
	)
		return (0);
	if (((map[game.exit_x][game.exit_y - 1] == PLAYER && map[game.exit_x][game.exit_y + 1] == COLLECTIBLE) ||
	 	(map[game.exit_x][game.exit_y + 1] == PLAYER && map[game.exit_x][game.exit_y - 1] == COLLECTIBLE)) &&
		rows <= 3)
		return (0);
	int x = 0;
	int y = 0;
	int exit_found = 0;

	push(s, game.player_x, game.player_y);
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
			if (in_visited(visited, game.exit_x, game.exit_y))
			{
				exit_found++;
				break;
			}
			get_next_moves(s, x, y, map, rows, cols, EXIT);
		}
	}
	free(visited);
	visited = NULL;
	visited = create_stack();

	// Part 2: Collectibles detection
	x = 0;
	y = 0;
	properties.collectibles = count_collectibles(map);
	int collectibles_found = 0;
	push(collectibles_stack, game.player_x, game.player_y);
	
		while (!is_empty(collectibles_stack))
		{
			Node *popped = pop(collectibles_stack);
			if (popped != NULL) {
    			x = popped->x;
    			y = popped->y;
			}
			if (in_visited(visited, x, y))
				continue;
			else
			{
				push(visited, x, y);
				if (in_visited(visited, x, y) && map[x][y] == COLLECTIBLE)
					collectibles_found++;
				if (collectibles_found == properties.collectibles)
					break;
				get_next_moves(collectibles_stack, x, y, map, rows, cols,COLLECTIBLE);
			}
		}
	free(s);
	free(visited);
	free(collectibles_stack);
	s = NULL;
	visited = NULL;
	collectibles_stack = NULL;
	if (exit_found && properties.collectibles == collectibles_found)
		return (1);
	else
		return (0);
}
