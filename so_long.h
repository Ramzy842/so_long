/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 03:49:25 by rchahban          #+#    #+#             */
/*   Updated: 2023/03/04 00:11:15 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define COLLECTIBLE 'C'
# define PLAYER 'P'
# define EXIT 'E'
# define SPACE '0'
# define WALL '1'

char	**read_map(char *map_path);
int		check_mandatory_conditions(char **map);
int		map_is_rectangular(char **map);
int		ft_strlen_2d(char **map);
int		count_players_number(char **map);
int		map_surrounded_by_walls(char **map);
#endif