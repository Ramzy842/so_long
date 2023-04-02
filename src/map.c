/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:49:38 by rchahban          #+#    #+#             */
/*   Updated: 2023/04/02 17:49:02 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"
#include "../get_next_line.h"

/* 1 - reading the map*/
void	fill_map(char *map_path, char **map)
{
	int		fd;
	char	*line;
	int		x;

	fd = open(map_path, O_RDONLY);
	line = get_next_line(fd);
	x = 0;
	while (line)
	{
		map[x] = line;
		x++;
		line = get_next_line(fd);
	}
}

char	**read_map(char *map_path)
{
	char	*line;
	char	**map;
	int		row_count;
	int		fd;

	fd = open(map_path, O_RDONLY);
	row_count = 0;
	line = get_next_line(fd);
	while (line)
	{
		row_count++;
		line = get_next_line(fd);
	}
	map = malloc(row_count * sizeof(char *) + 1);
	map[row_count] = NULL;
	close(fd);
	fill_map(map_path, map);
	return (map);
}

/* 2 -  The map must contain 1 exit, 
		at least 1 collectible, 
		and 1 starting position to
		be valid.*/
int	check_mandatory_conditions(char **map, int *exit_count, int *player_count)
{
	int	x;
	int	y;
	int	collectible_found;

	x = 0;
	y = 0;
	collectible_found = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] == PLAYER)
				(*player_count)++;
			if (map[x][y] == EXIT)
				(*exit_count)++;
			if (map[x][y] == COLLECTIBLE)
				collectible_found++;
			y++;
		}
		x++;
	}
	if (*exit_count == 1 && *player_count == 1 && collectible_found >= 1)
		return (1);
	return (0);
}

/* 3 - The map must be rectangular. */

int	map_is_rectangular(char **map, int cols)
{
	int	x;
	int	initial_col_length;
	int	current_col_length;

	x = 0;
	initial_col_length = cols;
	current_col_length = initial_col_length;
	while (map[x])
	{
		if (ft_strchr(map[x], '\n'))
			current_col_length = ft_strlen(map[x]) - 1;
		else
			current_col_length = ft_strlen(map[x]);
		if (current_col_length != initial_col_length)
			return (0);
		x++;
	}
	return (1);
}

/* 4 - The map must be closed/surrounded by walls. 
		If it’s not, the program must return
		an error. */

int	map_surrounded_by_walls(char **map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (!handle_first_line(map, &x, &y))
		return (0);
	x = 0;
	y = 0;
	if (!handle_last_line(map, &x, &y))
		return (0);
	x = 1;
	while (x < ft_strlen_2d(map) - 1)
	{
		if (map[x][0] != WALL || map[x][ft_strlen(map[x]) - 2] != WALL)
			return (0);
		x++;
	}
	return (1);
}
