/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:49:38 by rchahban          #+#    #+#             */
/*   Updated: 2023/03/19 12:51:22 by rchahban         ###   ########.fr       */
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
int	check_mandatory_conditions(char **map)
{
	int	x;
	int	y;
	int	player_found;
	int	collectible_found;
	int	exit_found;

	x = 0;
	y = 0;
	player_found = 0;
	collectible_found = 0;
	exit_found = 0;
	while(map[x])
	{
		y = 0;
		while(map[x][y])
		{
			if (map[x][y] ==  PLAYER)
				player_found++;
			if (map[x][y] == EXIT)
				exit_found++;
			if (map[x][y] == COLLECTIBLE)
				collectible_found++;
			y++;
		}
		x++;
	}
	if (exit_found == 1 && player_found == 1 && collectible_found >= 1)
		return (1);
	return (0);
}


/* 3 - The map must be rectangular. */

int	map_is_rectangular(char **map)
{
	int x;
	int initial_col_length;
	int current_col_length;

	x = 0;
	initial_col_length = ft_strlen(map[0]) - 1;
	current_col_length = initial_col_length;
	while (map[x])
	{
		if (ft_strchr(map[x], '\n'))
			current_col_length = ft_strlen(map[x]) - 1;
		else
			current_col_length = ft_strlen(map[x]);
		if (current_col_length != initial_col_length)
		{
			printf("* map is not rectangular\n");
			return (0);
		}
		x++;
	}
	printf("* map is rectangular\n");
	return (1);
}

/* 4 - The map must be closed/surrounded by walls. 
		If it’s not, the program must return
		an error. */

int	map_surrounded_by_walls(char **map)
{
	int	x;
	int	y;
	int	rows;
	int	length;

	x = 0;
	y = 0;
	rows = ft_strlen_2d(map);
	length = ft_strlen(map[0]) - 1;
	// check that first and last lines are all filled with '1'
	while (x < length)
	{
		if (map[0][x] != WALL)
		{
			printf("first line isn't surrounded with walls\n");
		}
		x++;
	}
	x = 0;
	while (x < length)
	{
		if (map[rows - 1][x] != WALL)
		{
			printf("last line isn't surrounded with walls\n");
		}
		x++;
	}
	// check that the lines in between start and end with '1'
	x = 1;
	while (x < rows - 1)
	{
		if (map[x][0] != WALL || map[x][length - 1] != WALL)
		{
			printf("the line %d is not surrounded by walls\n", x + 1);
		}
		x++;
	}
	return 0;
}

/* 5 - You have to check if there’s a valid path in the map. */

int	path_is_valid(char **map)
{
	int	x;

	x = 0;
	while (map[x])
	{
		
		x++;
	}
	return (0);
}

/* 6 - If the map contains a duplicates characters (exit/start),
	you should display an error message. */

int	count_players_number(char **map)
{
	int	x;
	int	y;
	int	player_count;

	x = 0;
	y = 0;
	player_count = 0;
	while(map[x])
	{
		y = 0;
		while(map[x][y])
		{
			if (map[x][y] == PLAYER)
				player_count++;
			y++;
		}
		x++;
	}
	if (player_count != 1)
		return (0);
	return (1);
}
