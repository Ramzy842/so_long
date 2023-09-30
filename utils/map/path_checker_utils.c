/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checker_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 17:55:37 by rchahban          #+#    #+#             */
/*   Updated: 2023/04/05 02:17:19 by rchahban         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../so_long.h"
#include "../../get_next_line.h"

void	push(t_Stack *stack, int x, int y)
{
	t_Node	*new_node;

	new_node = malloc(sizeof(t_Node));
	if (new_node == NULL)
		return ;
	new_node->x = x;
	new_node->y = y;
	new_node->next = stack->top;
	stack->top = new_node;
}

t_Stack	*create_stack(void)
{
	t_Stack	*stack;

	stack = malloc(sizeof(t_Stack));
	stack->top = NULL;
	return (stack);
}

int	is_empty(t_Stack *stack)
{
	return (stack->top == NULL);
}

void	get_next_moves(t_Stack *s, int a, int b, char goal)
{
	if (goal == EXIT)
	{
		if (a > 0 && g_game.map[a - 1][b] != WALL)
			push(s, a - 1, b);
		if (b < g_properties.map_cols && g_game.map[a][b + 1] != WALL)
			push(s, a, b + 1);
		if (a < g_properties.map_rows && g_game.map[a + 1][b] != WALL)
			push(s, a + 1, b);
		if (b > 0 && g_game.map[a][b - 1] != WALL)
			push(s, a, b - 1);
	}
	else
		collectible_moves(s, a, b);
}

t_Node	*pop(t_Stack *stack)
{
	t_Node	*temp;

	if (is_empty(stack))
		return (NULL);
	temp = stack->top;
	if (temp == NULL)
		return (NULL);
	stack->top = stack->top->next;
	temp->next = NULL;
	return (temp);
}
