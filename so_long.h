/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 03:49:25 by rchahban          #+#    #+#             */
/*   Updated: 2023/03/31 10:36:55 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>

# define COLLECTIBLE 'C'
# define PLAYER 'P'
# define EXIT 'E'
# define SPACE '0'
# define WALL '1'

typedef struct Props
{
	int map_cols;
	int map_rows;
	int collectibles;
} Props;

typedef struct Game
{
	char **map;
	int player_x;
	int player_y;
	int exit_x;
	int exit_y;
} Game;

Props		properties;
Game		game;

char	**read_map(char *map_path);
int		check_mandatory_conditions(char **map);
int		map_is_rectangular(char **map, int cols);
int		ft_strlen_2d(char **map);
int		map_surrounded_by_walls(char **map);
int	path_is_valid(char **map, int cols, int rows);

#endif