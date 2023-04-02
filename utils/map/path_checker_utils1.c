/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checker_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 17:55:37 by rchahban          #+#    #+#             */
/*   Updated: 2023/04/02 18:31:56 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"
#include "../../get_next_line.h"

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

void	collectible_moves(t_Stack *s, int a, int b)
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
