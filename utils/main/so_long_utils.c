/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 21:56:39 by rchahban          #+#    #+#             */
/*   Updated: 2023/04/03 22:40:02 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"
#include "../../get_next_line.h"

void	handle_two_img_cell(char c, int *x, int *y)
{
	if (c == 'P')
	{
		mlx_put_image_to_window(g_vars.mlx, g_vars.img,
			g_vars.floor, *y * 32, *x * 32);
		mlx_put_image_to_window(g_vars.mlx, g_vars.img,
			g_vars.player,
			*y * 32, *x * 32);
	}
	else if (c == 'C')
	{
		mlx_put_image_to_window(g_vars.mlx, g_vars.img,
			g_vars.floor, *y * 32, *x * 32);
		mlx_put_image_to_window(g_vars.mlx, g_vars.img, g_vars.collectible,
			*y * 32, *x * 32);
	}
}

void	handle_put_images(char **map, int *x, int *y)
{
	if (map[*x][*y] == '1')
	{
		mlx_put_image_to_window(g_vars.mlx, g_vars.img,
			g_vars.wall, *y * 32, *x * 32);
	}
	else if (map[*x][*y] == '0')
	{
		mlx_put_image_to_window(g_vars.mlx, g_vars.img,
			g_vars.floor, *y * 32, *x * 32);
	}
	else if (map[*x][*y] == 'E')
	{
		mlx_put_image_to_window(g_vars.mlx, g_vars.img,
			g_vars.exit, *y * 32, *x * 32);
	}
	else if (map[*x][*y] == 'P')
		handle_two_img_cell(map[*x][*y], x, y);
	else if (map[*x][*y] == 'C')
		handle_two_img_cell(map[*x][*y], x, y);
}

void	assign_images(char **map)
{
	int		x;
	int		y;

	x = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			handle_put_images(map, &x, &y);
			y++;
		}
		x++;
	}
}

int	key_hook(int keycode, t_vars *g_vars)
{
	static int			steps;
	static int			found_collectibles;
	static int			game_finished;

	if (keycode == 53)
	{
		mlx_destroy_window(g_vars->mlx, g_vars->img);
		mlx_destroy_image(g_vars->mlx, g_vars->collectible);
		mlx_destroy_image(g_vars->mlx, g_vars->exit);
		mlx_destroy_image(g_vars->mlx, g_vars->floor);
		mlx_destroy_image(g_vars->mlx, g_vars->player);
		mlx_destroy_image(g_vars->mlx, g_vars->wall);
		free(g_vars->mlx);
		free_map(g_game.map, g_properties.map_rows);
		exit(0);
	}
	if (keycode == 13 || keycode == 126)
		move_up(&steps, &found_collectibles, &game_finished);
	if (keycode == 2 || keycode == 124)
		move_right(&steps, &found_collectibles, &game_finished);
	if (keycode == 1 || keycode == 125)
		move_down(&steps, &found_collectibles, &game_finished);
	if (keycode == 0 || keycode == 123)
		move_left(&steps, &found_collectibles, &game_finished);
	return (0);
}

int	handle_destroy_event(int keycode, void *param)
{
	(void) keycode;
	(void) param;
	mlx_destroy_window(g_vars.mlx, g_vars.img);
	mlx_destroy_image(g_vars.mlx, g_vars.collectible);
	mlx_destroy_image(g_vars.mlx, g_vars.exit);
	mlx_destroy_image(g_vars.mlx, g_vars.floor);
	mlx_destroy_image(g_vars.mlx, g_vars.player);
	mlx_destroy_image(g_vars.mlx, g_vars.wall);
	free(g_vars.mlx);
	free_map(g_game.map, g_properties.map_rows);
	exit (0);
}
