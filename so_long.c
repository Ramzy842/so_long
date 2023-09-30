/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 03:57:29 by rchahban          #+#    #+#             */
/*   Updated: 2023/04/04 21:13:15 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "get_next_line.h"

void	free_map(char **map, int row_count)
{
	int	x;

	x = 0;
	while (x < row_count)
	{
		free(map[x]);
		x++;
	}
	free(map);
}

void	free_stack(t_Stack *stack)
{
	t_Node	*current;
	t_Node	*next;

	current = stack->top;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	free(current);
	free(stack);
}

void	free_nodes(t_Node *head)
{
	t_Node	*current;
	t_Node	*temp;

	current = head;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp);
	}
}

void	cleanup(void)
{
	mlx_destroy_window(g_vars.mlx, g_vars.img);
	free_map(g_game.map, g_properties.map_rows);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (0);
	if (!valid_extension(argv[1]))
	{
		write(1, "Error\n", 6);
		write(1, ".ber extension is not found!!\n", 30);
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
	cleanup();
	return (0);
}
