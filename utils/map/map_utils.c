/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 18:12:07 by rchahban          #+#    #+#             */
/*   Updated: 2023/04/02 17:49:05 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"

int	ft_strlen_2d(char **map)
{
	int	x;

	x = 0;
	while (map[x] != NULL)
	{
		x++;
	}
	return (x);
}

int	handle_first_line(char **map, int *x, int *y)
{
	while (*x < 1)
	{
		while (map[*x][*y] && map[*x][*y] != '\n')
		{
			if (map[*x][*y] != WALL)
				return (0);
			(*y)++;
		}
		(*x)++;
	}
	return (1);
}

int	handle_last_line(char **map, int *x, int *y)
{
	while (*x < 1)
	{
		while (map[ft_strlen_2d(map) - 1][*y]
			&& map[ft_strlen_2d(map) - 1][*y] != '\0')
		{
			if (map[ft_strlen_2d(map) - 1][*y] != WALL)
				return (0);
			(*y)++;
		}
		(*x)++;
	}
	return (1);
}
