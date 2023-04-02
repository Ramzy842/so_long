/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 21:21:17 by rchahban          #+#    #+#             */
/*   Updated: 2023/04/02 22:04:40 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"
#include "../../get_next_line.h"

void	end_game(int game_finished, int steps)
{
	(game_finished)++;
	(steps)++;
	printf("Movement count: %d\n", steps);
	printf("You win!\n");
	mlx_destroy_window(g_vars.mlx, g_vars.img);
	exit(0);
	return ;
}

void	move_up(int *steps, int *found_collectibles, int *game_finished)
{
	if ((g_game.map)[g_game.player_x - 1][g_game.player_y] == EXIT
			&& *found_collectibles == g_properties.collectibles
			&& !(*game_finished))
		end_game(*game_finished, *steps);
	if (g_game.player_x > 1
		&& (((g_game.map)[g_game.player_x - 1][g_game.player_y] != WALL
		&& (g_game.map)[g_game.player_x - 1][g_game.player_y] != EXIT))
		&& !(*game_finished))
	{
		(*steps)++;
		if ((g_game.map)
			[g_game.player_x - 1][g_game.player_y] == COLLECTIBLE)
			(*found_collectibles)++;
		(g_game.map)[g_game.player_x][g_game.player_y] = SPACE;
		g_game.player_x -= 1;
		(g_game.map)[g_game.player_x][g_game.player_y] = PLAYER;
		build_map(g_game.map, g_vars.mlx);
		printf("Movement count: %d\n", *steps);
	}
}

void	move_right(int *steps, int *found_collectibles, int *game_finished)
{
	if ((g_game.map)[g_game.player_x][g_game.player_y + 1] == EXIT
		&& *found_collectibles == g_properties.collectibles
		&& !(*game_finished))
		end_game(*game_finished, *steps);
	if (g_game.player_y < g_properties.map_cols - 2
		&& (((g_game.map)[g_game.player_x][g_game.player_y + 1] != WALL
		&& (g_game.map)[g_game.player_x][g_game.player_y + 1] != EXIT))
		&& !(*game_finished))
	{
		(*steps)++;
		if ((g_game.map)
			[g_game.player_x][g_game.player_y + 1] == COLLECTIBLE)
			(*found_collectibles)++;
		(g_game.map)[g_game.player_x][g_game.player_y] = SPACE;
		g_game.player_y += 1;
		(g_game.map)[g_game.player_x][g_game.player_y] = PLAYER;
		build_map(g_game.map, g_vars.mlx);
		printf("Movement count: %d\n", *steps);
	}
}

void	move_down(int *steps, int *found_collectibles, int *game_finished)
{
	if ((g_game.map)[g_game.player_x + 1][g_game.player_y] == EXIT
			&& *found_collectibles == g_properties.collectibles
			&& !(*game_finished))
		end_game(*game_finished, *steps);
	if (g_game.player_x < g_properties.map_rows - 2
		&& (((g_game.map)[g_game.player_x + 1][g_game.player_y] != WALL)
		&& ((g_game.map)[g_game.player_x + 1][g_game.player_y] != EXIT))
		&& !(*game_finished))
	{
		(*steps)++;
		if ((g_game.map)
			[g_game.player_x + 1][g_game.player_y] == COLLECTIBLE)
			(*found_collectibles)++;
		(g_game.map)[g_game.player_x][g_game.player_y] = SPACE;
		g_game.player_x += 1;
		(g_game.map)[g_game.player_x][g_game.player_y] = PLAYER;
		build_map(g_game.map, g_vars.mlx);
		printf("Movement count: %d\n", *steps);
	}
}

void	move_left(int *steps, int *found_collectibles, int *game_finished)
{
	if ((g_game.map)[g_game.player_x][g_game.player_y - 1] == EXIT
		&& *found_collectibles == g_properties.collectibles
		&& !(*game_finished))
		end_game(*game_finished, *steps);
	if (g_game.player_y > 1
		&& (((g_game.map)[g_game.player_x][g_game.player_y - 1] != WALL
		&& (g_game.map)[g_game.player_x][g_game.player_y - 1] != EXIT))
		&& !(*game_finished))
	{
		(*steps)++;
		if ((g_game.map)
			[g_game.player_x][g_game.player_y - 1] == COLLECTIBLE)
			(*found_collectibles)++;
		(g_game.map)[g_game.player_x][g_game.player_y] = SPACE;
		g_game.player_y -= 1;
		(g_game.map)[g_game.player_x][g_game.player_y] = PLAYER;
		build_map(g_game.map, g_vars.mlx);
		printf("Movement count: %d\n", *steps);
	}
}
