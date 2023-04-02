/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 08:01:53 by rchahban          #+#    #+#             */
/*   Updated: 2023/04/02 17:43:52 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"
#include "../../get_next_line.h"

typedef struct Node
{
	int				x;
	int				y;
	struct Node		*next;
}	t_Node;

typedef struct Stack
{
	t_Node	*top;
}	t_Stack;

void	push(t_Stack *stack, int x, int y)
{
	t_Node	*new_node;

	new_node = malloc(sizeof(t_Node));
	if (new_node == NULL)
		return ;
	new_node->x = x;
	new_node->y = y;
	new_node->next = stack->top;
	stack->top = new_node;
}

t_Stack	*create_stack(void)
{
	t_Stack	*stack;

	stack = malloc(sizeof(t_Stack));
	stack->top = NULL;
	return (stack);
}

int	is_empty(t_Stack *stack)
{
	return (stack->top == NULL);
}

void	get_next_moves(t_Stack *s, int a, int b, char goal)
{
	if (goal == EXIT)
	{
		if (a > 0 && g_game.map[a - 1][b] != WALL)
			push(s, a - 1, b);
		if (b < g_properties.map_cols && g_game.map[a][b + 1] != WALL)
			push(s, a, b + 1);
		if (a < g_properties.map_rows && g_game.map[a + 1][b] != WALL)
			push(s, a + 1, b);
		if (b > 0 && g_game.map[a][b - 1] != WALL)
			push(s, a, b - 1);
	}
	else
	{
		if (a > 0 && (g_game.map[a - 1][b] != WALL
			&& g_game.map[a - 1][b] != EXIT))
			push(s, a - 1, b);
		if (b < g_properties.map_cols
			&& (g_game.map[a][b + 1] != WALL
			&& g_game.map[a][b + 1] != EXIT))
			push(s, a, b + 1);
		if (a < g_properties.map_rows
			&& (g_game.map[a + 1][b] != WALL
			&& g_game.map[a + 1][b] != EXIT))
			push(s, a + 1, b);
		if (b > 0 && (g_game.map[a][b - 1] != WALL
			&& g_game.map[a][b - 1] != EXIT))
			push(s, a, b - 1);
	}
}

t_Node	*pop(t_Stack *stack)
{
	t_Node	*temp;
	int		x;
	int		y;

	if (is_empty(stack))
		return (NULL);
	temp = malloc(sizeof(t_Node));
	if (temp == NULL)
		return (NULL);
	x = stack->top->x;
	y = stack->top->y;
	temp = stack->top;
	stack->top = stack->top->next;
	return (temp);
}

void	display_stack(t_Stack *stack)
{
	t_Node	*temp;
	int		x;

	x = 0;
	if (is_empty(stack))
		printf("Stack is Empty!\n");
	else
	{
		temp = malloc(sizeof(t_Node));
		temp = stack->top;
		while (temp != NULL)
		{
			printf("|[%d][%d]|\n", temp->x, temp->y);
			temp = temp->next;
			x++;
		}
	}
}

int	in_visited(t_Stack	*visited, int a, int b)
{
	t_Node	*temp;

	if (is_empty(visited))
		return (0);
	else
	{
		temp = malloc(sizeof(t_Node));
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

int	count_collectibles(char **map)
{
	int	x;
	int	y;
	int	collectibles;

	x = 0;
	y = 0;
	collectibles = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] == COLLECTIBLE)
				collectibles++;
			y++;
		}
		x++;
	}
	return (collectibles);
}

void	assign_point(void)
{
	int	x;
	int	y;

	x = 0;
	while (g_game.map[x] != NULL)
	{
		y = 0;
		while (g_game.map[x][y] != '\0')
		{
			if (g_game.map[x][y] == 'P')
			{
				g_game.player_x = x;
				g_game.player_y = y;
			}
			if (g_game.map[x][y] == 'E')
			{
				g_game.exit_x = x;
				g_game.exit_y = y;
			}
			y++;
		}
		x++;
	}
}

int	path_is_valid(char **map)
{
	t_Stack	*s;
	t_Stack	*visited;
	t_Stack	*collectibles_stack;
	t_Node	*popped;
	int		x;
	int		y;
	int		exit_found;
	int		collectibles_found;

	s = create_stack();
	visited = create_stack();
	collectibles_stack = create_stack();
	x = 0;
	y = 0;
	exit_found = 0;
	collectibles_found = 0;
	assign_point();
	if (map[g_game.exit_x + 1][g_game.exit_y] == WALL
		&& map[g_game.exit_x - 1][g_game.exit_y] == WALL
		&& map[g_game.exit_x][g_game.exit_y + 1] == WALL
		&& map[g_game.exit_x][g_game.exit_y - 1] == WALL
	)
		return (0);
	if (((map[g_game.exit_x][g_game.exit_y - 1] == PLAYER
			&& map[g_game.exit_x][g_game.exit_y + 1] == COLLECTIBLE)
			|| (map[g_game.exit_x][g_game.exit_y + 1] == PLAYER
			&& map[g_game.exit_x][g_game.exit_y - 1] == COLLECTIBLE))
			&& g_properties.map_rows <= 3)
		return (0);
	push(s, g_game.player_x, g_game.player_y);
	while (!is_empty(s))
	{
		popped = pop(s);
		if (popped != NULL)
		{
			x = popped->x;
			y = popped->y;
		}
		if (in_visited(visited, x, y))
			continue ;
		else
		{
			push(visited, x, y);
			if (in_visited(visited, g_game.exit_x, g_game.exit_y))
			{
				exit_found++;
				break ;
			}
			get_next_moves(s, x, y, EXIT);
		}
	}
	free(visited);
	visited = NULL;
	visited = create_stack();
	x = 0;
	y = 0;
	g_properties.collectibles = count_collectibles(map);
	push(collectibles_stack, g_game.player_x, g_game.player_y);
	while (!is_empty(collectibles_stack))
	{
		popped = pop(collectibles_stack);
		if (popped != NULL)
		{
			x = popped->x;
			y = popped->y;
		}
		if (in_visited(visited, x, y))
			continue ;
		else
		{
			push(visited, x, y);
			if (in_visited(visited, x, y) && map[x][y] == COLLECTIBLE)
				collectibles_found++;
			if (collectibles_found == g_properties.collectibles)
				break ;
			get_next_moves(collectibles_stack, x, y, COLLECTIBLE);
		}
	}
	free(s);
	free(visited);
	free(collectibles_stack);
	s = NULL;
	visited = NULL;
	collectibles_stack = NULL;
	if (exit_found && g_properties.collectibles == collectibles_found)
		return (1);
	else
		return (0);
}
