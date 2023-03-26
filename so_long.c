/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 03:57:29 by rchahban          #+#    #+#             */
/*   Updated: 2023/03/26 21:01:04 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "get_next_line.h"

int	main(int argc, char **argv)
{
	char		**map;
	size_t		x;
	size_t		y;

	if (argc != 2)
		return (0);
	map = read_map(argv[1]);
	x = 0;
	while (map[x] != NULL)
	{
		y = 0;
		while (y < ft_strlen(map[x]))
		{
			printf("%c", map[x][y]);
			y++;
		}
		x++;
	}
	printf("\n");
	/* if (check_mandatory_conditions(map) == 1)
		printf("\n* mandatory conditions achieved!\n");
	else
		printf("\n* mandatory conditions are not achieved!\n");
	map_is_rectangular(map);
	if (count_players_number(map) == 1)
		printf("* One Player Present\n");
	else if (count_players_number(map) == 0)
		printf("* Player Count is Wrong\n");
	map_surrounded_by_walls(map);
	path_is_valid(map); */
	if (check_mandatory_conditions(map) && map_is_rectangular(map) 
	&& count_players_number(map) && map_surrounded_by_walls(map) 
	&& path_is_valid(map))
		printf("map is valid!\n");
	else
		printf("map is not valid!\n");
	free(map);
	return (0);
}
