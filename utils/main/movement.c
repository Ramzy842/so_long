/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 21:21:17 by rchahban          #+#    #+#             */
/*   Updated: 2023/04/03 02:45:49 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"
#include "../../get_next_line.h"

void	end_game(int game_finished, int steps)
{
	(game_finished)++;
	(steps)++;
	write(1, "Movement count: ", 16);
	ft_putnbr(steps);
	write(1, "\n", 1);
	write(1, "You win!\n", 10);
	mlx_destroy_window(g_vars.mlx, g_vars.img);
	mlx_destroy_image(g_vars.mlx, g_vars.collectible);
	mlx_destroy_image(g_vars.mlx, g_vars.exit);
	mlx_destroy_image(g_vars.mlx, g_vars.floor);
	mlx_destroy_image(g_vars.mlx, g_vars.player);
	mlx_destroy_image(g_vars.mlx, g_vars.wall);
	free_map(g_game.map, g_properties.map_rows);
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
		write(1, "Movement count: ", 16);
		ft_putnbr(*steps);
		write(1, "\n", 1);
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
		write(1, "Movement count: ", 16);
		ft_putnbr(*steps);
		write(1, "\n", 1);
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
		write(1, "Movement count: ", 16);
		ft_putnbr(*steps);
		write(1, "\n", 1);
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
		write(1, "Movement count: ", 16);
		ft_putnbr(*steps);
		write(1, "\n", 1);
	}
}
