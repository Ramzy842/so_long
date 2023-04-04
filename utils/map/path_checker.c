/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 08:01:53 by rchahban          #+#    #+#             */
/*   Updated: 2023/04/04 20:22:33 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"
#include "../../get_next_line.h"

void	search_exit(t_Stack *s, t_Stack *visited,
	t_Node *popped, int *exit_found)
{
	int		x;
	int		y;

	while (!is_empty(s))
	{
		popped = pop(s);
		if (popped != NULL)
		{
			x = popped->x;
			y = popped->y;
			free(popped);
		}
		if (in_visited(visited, x, y))
			continue ;
		else
		{
			push(visited, x, y);
			if (in_visited(visited, g_game.exit_x, g_game.exit_y))
			{
				(*exit_found)++;
				break ;
			}
			get_next_moves(s, x, y, EXIT);
		}
	}
}

void	search_collectibles(t_Stack *collectibles_stack,
	t_Stack *visited, t_Node *popped, int *collectibles_found)
{
	int		x;
	int		y;

	while (!is_empty(collectibles_stack))
	{
		popped = pop(collectibles_stack);
		if (popped != NULL)
		{
			x = popped->x;
			y = popped->y;
			free(popped);
		}
		if (in_visited(visited, x, y))
			continue ;
		else
		{
			push(visited, x, y);
			if (in_visited(visited, x, y) && g_game.map[x][y] == COLLECTIBLE)
				(*collectibles_found)++;
			if (*collectibles_found == g_properties.collectibles)
				break ;
			get_next_moves(collectibles_stack, x, y, COLLECTIBLE);
		}
	}
}

int	exit_path(t_Stack *s, t_Stack *visited, t_Node *popped)
{
	int		exit_found;

	exit_found = 0;
	push(s, g_game.player_x, g_game.player_y);
	search_exit(s, visited, popped, &exit_found);
	free_stack(s);
	free_stack(visited);
	s = NULL;
	visited = NULL;
	return (exit_found);
}

int	collectible_path(t_Stack *collectibles_stack,
	t_Stack *visited, t_Node *popped)
{
	int		x;
	int		y;
	int		collectibles_found;

	x = 0;
	y = 0;
	collectibles_found = 0;
	visited = create_stack();
	g_properties.collectibles = count_collectibles(g_game.map);
	push(collectibles_stack, g_game.player_x, g_game.player_y);
	search_collectibles(collectibles_stack, visited,
		popped, &collectibles_found);
	free_stack(visited);
	free_stack(collectibles_stack);
	visited = NULL;
	collectibles_stack = NULL;
	if (g_properties.collectibles == collectibles_found)
		return (1);
	return (0);
}

int	path_is_valid(char **map)
{
	t_Stack	*s;
	t_Stack	*visited;
	t_Stack	*collectibles_stack;
	t_Node	*popped;

	s = create_stack();
	visited = create_stack();
	collectibles_stack = create_stack();
	popped = NULL;
	free_nodes(popped);
	assign_point();
	if (!handle_exit_surrounded_by_walls(map))
		return (0);
	if (!handle_3r_map(map))
		return (0);
	if (exit_path(s, visited, popped)
		&& collectible_path(collectibles_stack, visited, popped))
		{
		return (1);
			
		}
	else
		return (0);
}
