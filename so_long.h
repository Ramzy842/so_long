/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 03:49:25 by rchahban          #+#    #+#             */
/*   Updated: 2023/04/02 22:14:55 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
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

typedef struct Node
{
	int				x;
	int				y;
	struct Node		*next;
}	t_Node;

typedef struct Stack
{
	t_Node	*top;
}	t_Stack;

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
void	push(t_Stack *stack, int x, int y);
t_Stack	*create_stack(void);
int		is_empty(t_Stack *stack);
void	get_next_moves(t_Stack *s, int a, int b, char goal);
t_Node	*pop(t_Stack *stack);
int		in_visited(t_Stack	*visited, int a, int b);
int		count_collectibles(char **map);
void	collectible_moves(t_Stack *s, int a, int b);
void	assign_point(void);
int		handle_exit_surrounded_by_walls(char **map);
int		handle_3r_map(char **map);
void	move_up(int *steps, int *found_collectibles, int *game_finished);
void	move_right(int *steps, int *found_collectibles, int *game_finished);
void	move_down(int *steps, int *found_collectibles, int *game_finished);
void	move_left(int *steps, int *found_collectibles, int *game_finished);
void	build_map(char **map, void *mlx);
void	assign_images(char **map);
int		key_hook(int keycode, t_vars *g_vars);
int		handle_destroy_event(int keycode, void *param);
int		valid_extension(char *path);
void	initialize_g_properties(char *map_path);
void	start_game(void);
void	display_errors(void);
#endif