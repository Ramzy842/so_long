/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 21:56:39 by rchahban          #+#    #+#             */
/*   Updated: 2023/04/05 01:24:11 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"
#include "../../get_next_line.h"

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

int	valid_extension(char *path)
{
	int	path_length;

	path_length = ft_strlen(path);
	return (path[path_length - 1] == 'r' && path[path_length - 2] == 'e'
		&& path[path_length - 3] == 'b' && path[path_length - 4] == '.');
}

void	initialize_g_properties(char *map_path)
{
	g_vars.mlx = mlx_init();
	g_game.map = read_map(map_path);
	g_properties.map_cols = ft_strlen(g_game.map[0]) - 1;
	g_properties.map_rows = ft_strlen_2d(g_game.map);
	g_properties.exit_count = 0;
	g_properties.player_count = 0;
	g_vars.img = mlx_new_window(g_vars.mlx, g_properties.map_cols * 32,
			g_properties.map_rows * 32, "so_long");
}

void	start_game(void)
{
	build_map(g_game.map, g_vars.mlx);
	mlx_key_hook(g_vars.img, key_hook, &g_vars);
	mlx_hook(g_vars.img, 17, 0, handle_destroy_event, NULL);
	mlx_loop(g_vars.mlx);
}

void	display_errors(void)
{
	write(1, "Error\n", 6);
	if (g_properties.exit_count > 1)
		write(1, "* Didn't find 1 Exit only!\n", 27);
	if (g_properties.player_count > 1)
		write(1, "* Didn't find 1 Player only!\n", 29);
	write(1, "--- map is not valid! ---\n", 26);
}
