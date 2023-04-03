/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checker_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 17:55:37 by rchahban          #+#    #+#             */
/*   Updated: 2023/04/03 19:25:12 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"
#include "../../get_next_line.h"

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

int	handle_exit_surrounded_by_walls(char **map)
{
	if (map[g_game.exit_x + 1][g_game.exit_y] == WALL
		&& map[g_game.exit_x - 1][g_game.exit_y] == WALL
		&& map[g_game.exit_x][g_game.exit_y + 1] == WALL
		&& map[g_game.exit_x][g_game.exit_y - 1] == WALL
	)
		return (0);
	return (1);
}

int	handle_3r_map(char **map)
{
	if (((map[g_game.exit_x][g_game.exit_y - 1] == PLAYER
			&& map[g_game.exit_x][g_game.exit_y + 1] == COLLECTIBLE)
			|| (map[g_game.exit_x][g_game.exit_y + 1] == PLAYER
			&& map[g_game.exit_x][g_game.exit_y - 1] == COLLECTIBLE))
			&& g_properties.map_rows <= 3)
		return (0);
	return (1);
}
