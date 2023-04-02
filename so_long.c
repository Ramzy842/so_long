/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 03:57:29 by rchahban          #+#    #+#             */
/*   Updated: 2023/04/02 22:12:17 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "get_next_line.h"

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
	initialize_g_properties(argv[1]);
	if (check_mandatory_conditions(g_game.map, &(g_properties.exit_count),
			&(g_properties.player_count))
		&& map_is_rectangular(g_game.map, g_properties.map_cols)
		&& map_surrounded_by_walls(g_game.map)
		&& path_is_valid(g_game.map))
		start_game();
	else
		display_errors();
	free(g_game.map);
	return (0);
}
