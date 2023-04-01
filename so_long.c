/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 03:57:29 by rchahban          #+#    #+#             */
/*   Updated: 2023/04/01 02:37:48 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "get_next_line.h"


void		*img = NULL;
void		*mlx;
int			found_collectibles;
int			steps;
int			game_finished;

void build_map(char **map,void *mlx,void *img)
{
	int		img_width;
	int		img_height;
	void	*floor;
	void	*wall;
	void	*collectible;
	void	*player;
	void	*exit;
	int		x;
	int		y;
	
	img_width = 32;
	img_height = 32;
	floor = mlx_xpm_file_to_image(mlx,"./src/assets/floor.xpm",&img_width,&img_height);
	player = mlx_xpm_file_to_image(mlx,"./src/assets/player.xpm",&img_width,&img_height);
	collectible = mlx_xpm_file_to_image(mlx,"./src/assets/collectible.xpm",&img_width,&img_height);
	wall = mlx_xpm_file_to_image(mlx,"./src/assets/wall.xpm",&img_width,&img_height);
	exit = mlx_xpm_file_to_image(mlx,"./src/assets/exit.xpm",&img_width,&img_height);
	x = 0;
	y = 0;
	while(map[x])
	{
		y = 0;
		while(map[x][y])
		{
			if(map[x][y] == '1')
			{
				mlx_put_image_to_window(mlx, img, wall, y*32, x*32);
			}
			else if(map[x][y] == '0')
			{
				mlx_put_image_to_window(mlx, img, floor, y*32, x*32);
			}
			else if(map[x][y] == 'E')
			{
				mlx_put_image_to_window(mlx, img, exit, y*32, x*32);
			}
			else if(map[x][y] == 'P')
			{
				mlx_put_image_to_window(mlx, img, floor, y*32, x*32);
				mlx_put_image_to_window(mlx, img, player, y*32, x*32);
			}
			else if(map[x][y] == 'C')
			{
				mlx_put_image_to_window(mlx, img, floor, y*32, x*32);
				mlx_put_image_to_window(mlx, img, collectible, y*32, x*32);
			}
			y++;
		}
		x++;
	}
}

int	key_hook(int keycode)
{
	if (keycode == 53)
	{
		mlx_destroy_window(mlx, img);
		exit(1);
	}
	if (keycode == 13 || keycode == 126)
	{
		
		if ((game.map)[game.player_x - 1][game.player_y] == EXIT && found_collectibles == properties.collectibles && !game_finished)
		{
			game_finished++;
			steps++;
			printf("Steps: %d\n", steps);
			printf("You win!\n");
			
			return (0);
		}
		if (game.player_x > 1 && (((game.map)[game.player_x - 1][game.player_y] != WALL && (game.map)[game.player_x - 1][game.player_y] != EXIT)) && !game_finished)
		{
			steps++;
			if ((game.map)[game.player_x - 1][game.player_y] == COLLECTIBLE)
				found_collectibles++;
			(game.map)[game.player_x][game.player_y] = SPACE;
			game.player_x -= 1;
			(game.map)[game.player_x][game.player_y] = PLAYER;
			build_map(game.map, mlx, img);
			printf("Steps: %d\n", steps);
			
		}
		
	}
	if (keycode == 2 || keycode == 124)
	{
		if ((game.map)[game.player_x][game.player_y + 1] == EXIT && found_collectibles == properties.collectibles && !game_finished)
		{
			game_finished++;
			steps++;
			printf("Steps: %d\n", steps);
			printf("You win!\n");
			return (0);
		}
		if (game.player_y < properties.map_cols - 2 && (((game.map)[game.player_x][game.player_y + 1] != WALL && (game.map)[game.player_x][game.player_y + 1] != EXIT)) && !game_finished)
		{
			steps++;
			if ((game.map)[game.player_x][game.player_y + 1] == COLLECTIBLE)
				found_collectibles++;
			(game.map)[game.player_x][game.player_y] = SPACE;
			game.player_y += 1;
			(game.map)[game.player_x][game.player_y] = PLAYER;
			build_map(game.map, mlx, img);
			printf("Steps: %d\n", steps);
		}
		
	}
	if (keycode == 1 || keycode == 125)
	{
		if ((game.map)[game.player_x + 1][game.player_y] == EXIT && found_collectibles == properties.collectibles && !game_finished)
		{
			game_finished++;
			steps++;
			printf("Steps: %d\n", steps);
			printf("You win!\n");
			return (0);
		}
		if (game.player_x < properties.map_rows - 2 && (((game.map)[game.player_x + 1][game.player_y] != WALL) && ((game.map)[game.player_x + 1][game.player_y] != EXIT)) && !game_finished)
		{
			steps++;
			if ((game.map)[game.player_x + 1][game.player_y] == COLLECTIBLE)
				found_collectibles++;
			(game.map)[game.player_x][game.player_y] = SPACE;
			game.player_x += 1;
			(game.map)[game.player_x][game.player_y] = PLAYER;
			build_map(game.map, mlx, img);
			printf("Steps: %d\n", steps);
		}
	}
	if (keycode == 0 || keycode == 123)
	{
		if ((game.map)[game.player_x][game.player_y - 1] == EXIT && found_collectibles == properties.collectibles && !game_finished)
		{
			game_finished++;
			steps++;
			printf("Steps: %d\n", steps);
			printf("You win!\n");
			return (0);
		}
		if (game.player_y > 1 && (((game.map)[game.player_x][game.player_y - 1] != WALL && (game.map)[game.player_x][game.player_y - 1] != EXIT)) && !game_finished)
		{
			steps++;
			if ((game.map)[game.player_x][game.player_y - 1] == COLLECTIBLE)
				found_collectibles++;
			(game.map)[game.player_x][game.player_y] = SPACE;
			game.player_y -= 1;
			(game.map)[game.player_x][game.player_y] = PLAYER;
			build_map(game.map, mlx, img);
			printf("Steps: %d\n", steps);
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (0);
	mlx = mlx_init();
	game.map = read_map(argv[1]);
	properties.map_cols = ft_strlen(game.map[0]) - 1;
	properties.map_rows = ft_strlen_2d(game.map);
	img = mlx_new_window(mlx, properties.map_cols * 32, properties.map_rows * 32, "so_long");
	if (game_finished)
	{
		mlx_destroy_window(mlx, img);
		exit(1);
	}
	if (check_mandatory_conditions(game.map) && map_is_rectangular(game.map, properties.map_cols)
		&& map_surrounded_by_walls(game.map) && path_is_valid(game.map, properties.map_cols, properties.map_rows))
		{
			build_map(game.map, mlx, img);
			mlx_key_hook(img, key_hook, NULL);
			mlx_loop(mlx);
		}
	else
		printf("--- map is not valid! ---\n");
	free(game.map);
	return (0);
}
