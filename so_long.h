/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 03:49:25 by rchahban          #+#    #+#             */
/*   Updated: 2023/04/02 17:49:33 by rchahban         ###   ########.fr       */
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
	int	map_cols;
	int	map_rows;
	int	collectibles;
	int	player_count;
	int	exit_count;
}	t_Props;

typedef struct Game
{
	char	**map;
	int		player_x;
	int		player_y;
	int		exit_x;
	int		exit_y;
}	t_Game;

typedef struct s_vars {
	void	*mlx;
	void	*img;
	void	*floor;
	void	*wall;
	void	*collectible;
	void	*player;
	void	*exit;
}				t_vars;

t_vars		g_vars;

t_Props		g_properties;
t_Game		g_game;

char	**read_map(char *map_path);
int		check_mandatory_conditions(char **map,
			int *exit_count, int *player_count);
int		map_is_rectangular(char **map, int cols);
int		ft_strlen_2d(char **map);
int		map_surrounded_by_walls(char **map);
int		path_is_valid(char **map);
int		handle_first_line(char **map, int *x, int *y);
int		handle_last_line(char **map, int *x, int *y);
#endif