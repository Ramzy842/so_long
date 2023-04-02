/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 03:57:29 by rchahban          #+#    #+#             */
/*   Updated: 2023/04/02 17:06:30 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "get_next_line.h"

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

void	build_map(char **map, void *mlx)
{
	int		img_width;
	int		img_height;

	img_width = 32;
	img_height = 32;
	g_vars.floor = mlx_xpm_file_to_image(mlx, "./src/assets/floor.xpm",
			&img_width, &img_height);
	g_vars.player = mlx_xpm_file_to_image(mlx, "./src/assets/player.xpm",
			&img_width, &img_height);
	g_vars.collectible = mlx_xpm_file_to_image(mlx,
			"./src/assets/collectible.xpm",
			&img_width, &img_height);
	g_vars.wall = mlx_xpm_file_to_image(mlx, "./src/assets/wall.xpm",
			&img_width, &img_height);
	g_vars.exit = mlx_xpm_file_to_image(mlx, "./src/assets/exit.xpm",
			&img_width, &img_height);
	assign_images(map);
}

int	handle_destroy_event(int keycode, void *param)
{
	(void) keycode;
	(void) param;
	exit (0);
}

int	key_hook(int keycode, t_vars *g_vars)
{
	static int			steps;
	static int			found_collectibles;
	static int			game_finished;

	if (keycode == 53)
	{
		mlx_destroy_window(g_vars->mlx, g_vars->img);
		exit(0);
	}
	if (keycode == 13 || keycode == 126)
	{
		if ((g_game.map)[g_game.player_x - 1][g_game.player_y] == EXIT
			&& found_collectibles == g_properties.collectibles
			&& !game_finished)
		{
			game_finished++;
			steps++;
			printf("Movement count: %d\n", steps);
			printf("You win!\n");
			mlx_destroy_window(g_vars->mlx, g_vars->img);
			exit(0);
			return (0);
		}
		if (g_game.player_x > 1
			&& (((g_game.map)[g_game.player_x - 1][g_game.player_y] != WALL
			&& (g_game.map)[g_game.player_x - 1][g_game.player_y] != EXIT))
			&& !game_finished)
		{
			steps++;
			if ((g_game.map)
				[g_game.player_x - 1][g_game.player_y] == COLLECTIBLE)
				found_collectibles++;
			(g_game.map)[g_game.player_x][g_game.player_y] = SPACE;
			g_game.player_x -= 1;
			(g_game.map)[g_game.player_x][g_game.player_y] = PLAYER;
			build_map(g_game.map, g_vars->mlx);
			printf("Movement count: %d\n", steps);
		}
	}
	if (keycode == 2 || keycode == 124)
	{
		if ((g_game.map)[g_game.player_x][g_game.player_y + 1] == EXIT
			&& found_collectibles == g_properties.collectibles
			&& !game_finished)
		{
			game_finished++;
			steps++;
			printf("Movement count: %d\n", steps);
			printf("You win!\n");
			mlx_destroy_window(g_vars->mlx, g_vars->img);
			exit(0);
			return (0);
		}
		if (g_game.player_y < g_properties.map_cols - 2
			&& (((g_game.map)[g_game.player_x][g_game.player_y + 1] != WALL
			&& (g_game.map)[g_game.player_x][g_game.player_y + 1] != EXIT))
			&& !game_finished)
		{
			steps++;
			if ((g_game.map)
				[g_game.player_x][g_game.player_y + 1] == COLLECTIBLE)
				found_collectibles++;
			(g_game.map)[g_game.player_x][g_game.player_y] = SPACE;
			g_game.player_y += 1;
			(g_game.map)[g_game.player_x][g_game.player_y] = PLAYER;
			build_map(g_game.map, g_vars->mlx);
			printf("Movement count: %d\n", steps);
		}
	}
	if (keycode == 1 || keycode == 125)
	{
		if ((g_game.map)[g_game.player_x + 1][g_game.player_y] == EXIT
			&& found_collectibles == g_properties.collectibles
			&& !game_finished)
		{
			game_finished++;
			steps++;
			printf("Movement count: %d\n", steps);
			printf("You win!\n");
			mlx_destroy_window(g_vars->mlx, g_vars->img);
			exit(0);
			return (0);
		}
		if (g_game.player_x < g_properties.map_rows - 2
			&& (((g_game.map)[g_game.player_x + 1][g_game.player_y] != WALL)
			&& ((g_game.map)[g_game.player_x + 1][g_game.player_y] != EXIT))
			&& !game_finished)
		{
			steps++;
			if ((g_game.map)
				[g_game.player_x + 1][g_game.player_y] == COLLECTIBLE)
				found_collectibles++;
			(g_game.map)[g_game.player_x][g_game.player_y] = SPACE;
			g_game.player_x += 1;
			(g_game.map)[g_game.player_x][g_game.player_y] = PLAYER;
			build_map(g_game.map, g_vars->mlx);
			printf("Movement count: %d\n", steps);
		}
	}
	if (keycode == 0 || keycode == 123)
	{
		if ((g_game.map)[g_game.player_x][g_game.player_y - 1] == EXIT
			&& found_collectibles == g_properties.collectibles
			&& !game_finished)
		{
			game_finished++;
			steps++;
			printf("Movement count: %d\n", steps);
			printf("You win!\n");
			mlx_destroy_window(g_vars->mlx, g_vars->img);
			exit(0);
			return (0);
		}
		if (g_game.player_y > 1
			&& (((g_game.map)[g_game.player_x][g_game.player_y - 1] != WALL
			&& (g_game.map)[g_game.player_x][g_game.player_y - 1] != EXIT))
			&& !game_finished)
		{
			steps++;
			if ((g_game.map)
				[g_game.player_x][g_game.player_y - 1] == COLLECTIBLE)
				found_collectibles++;
			(g_game.map)[g_game.player_x][g_game.player_y] = SPACE;
			g_game.player_y -= 1;
			(g_game.map)[g_game.player_x][g_game.player_y] = PLAYER;
			build_map(g_game.map, g_vars->mlx);
			printf("Movement count: %d\n", steps);
		}
	}
	return (0);
}

int	valid_extension(char *path)
{
	int	x;
	int	path_length;

	x = 0;
	path_length = ft_strlen(path);
	return (path[path_length - 1] == 'r' && path[path_length - 2] == 'e'
		&& path[path_length - 3] == 'b' && path[path_length - 4] == '.');
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (0);
	if (!valid_extension(argv[1]))
	{
		write(1, "Error\n", 6);
		printf(".ber extension is not found!!\n");
		return (0);
	}
	g_vars.mlx = mlx_init();
	g_game.map = read_map(argv[1]);
	g_properties.map_cols = ft_strlen(g_game.map[0]) - 1;
	g_properties.map_rows = ft_strlen_2d(g_game.map);
	g_properties.exit_count = 0;
	g_properties.player_count = 0;
	g_vars.img = mlx_new_window(g_vars.mlx, g_properties.map_cols * 32,
			g_properties.map_rows * 32, "so_long");
	if (check_mandatory_conditions(g_game.map, &(g_properties.exit_count),
			&(g_properties.player_count))
		&& map_is_rectangular(g_game.map, g_properties.map_cols)
		&& map_surrounded_by_walls(g_game.map)
		&& path_is_valid(g_game.map))
	{
		build_map(g_game.map, g_vars.mlx);
		mlx_key_hook(g_vars.img, key_hook, &g_vars);
		mlx_hook(g_vars.img, 17, 0, handle_destroy_event, NULL);
		mlx_loop(g_vars.mlx);
	}
	else
	{
		write(1, "Error\n", 6);
		if (g_properties.exit_count > 1)
			printf("* Didn't find 1 Exit only!\n");
		if (g_properties.player_count > 1)
			printf("* Didn't find 1 Player only!\n");
		printf("--- map is not valid! ---\n");
	}
	free(g_game.map);
	return (0);
}
