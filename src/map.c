/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:49:38 by rchahban          #+#    #+#             */
/*   Updated: 2023/03/22 07:44:30 by rchahban         ###   ########.fr       */
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

typedef struct Node
{
	int x;
	int y;
	struct Node *next;
} Node;

typedef struct Stack
{
	Node *top;
} Stack;

void push(Stack *stack ,int x, int y)
{
	Node *newNode = malloc(sizeof(Node));
	if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
	newNode->x = x;
	newNode->y = y;
	newNode->next = stack->top;
	stack->top = newNode;
}

Stack *create_stack()
{
	Stack *stack = malloc(sizeof(Stack));
	stack->top = NULL;
	return stack;
}

int is_empty(Stack *stack)
{
	return (stack->top == NULL);
}

void get_next_moves(Stack *s, int a, int b, char **map)
{
	if (a > 0 && map[a - 1][b] != '1')
		push(s, a - 1, b);
	if (b < 6 && map[a][b + 1] != '1' )
		push(s, a, b + 1);
	if (a < 5 && map[a + 1][b] != '1')
		push(s, a + 1, b);
	if (b > 0 && map[a][b - 1] != '1')
		push(s, a, b - 1);
}

Node *pop(Stack *stack)
{
	if (is_empty(stack)) {
		printf("Stack Underflow\n");
		return NULL;
    }
	Node *temp = malloc(sizeof(Node));
	if (temp == NULL) {
    	printf("Memory allocation failed\n");
    	return NULL;
	}
	int x;
	int y;

	x = stack->top->x;
	y = stack->top->y;
	temp = stack->top;
	stack->top = stack->top->next;
	printf("popped [%d][%d]\n", temp->x, temp->y);
	return temp;
}

void peek(Stack *stack)
{
	if (is_empty(stack))
		printf("Stack is empty!\n");
	else
	{
		printf("top value is: [%d][%d]\n", stack->top->x, stack->top->y);
	}
}



int count_nodes(Stack *stack)
{
	int x;

	x = 0;
	Node *temp = stack->top;
	while(temp != NULL)
	{
		x++;
		temp = temp->next;
	}
	return x;
}

void display_stack(Stack *stack)
{
	if (is_empty(stack))
		printf("Stack is Empty!\n");
	else {
		Node *temp = malloc(sizeof(Node));
		temp = stack->top;
		while (temp != NULL)
		{
			printf("|[%d][%d]|\n", temp->x, temp->y);
			temp = temp->next;
		}
	}
}

int in_visited(Stack *visited, int a, int b)
{
	if (is_empty(visited))
		printf("Visited Stack is Empty!\n");
	else {
		Node *temp = malloc(sizeof(Node));
		temp = visited->top;
		while (temp != NULL)
		{
			if (a == temp->x && b == temp->y)
				return (1);
			temp = temp->next;
		}
	}	
	return (0);
}

void	path_is_valid(char **map)
{
	// start from player position
// push coordinates and pop it
	// check if the popped coordinates is in the visited nodes stack
	// if so ignore coordinates and pop next coordinates in stack
	// else continue
	// put coordinates in visited stack
	// check if the coordinates are the Exit
		// if true --> print path is valid
// else 
// add adjacent coordinates to stack
// recurse from step 1

	Stack *s = create_stack();
	Stack *visited = create_stack();

	int start_x = 1;
	int start_y = 5;
	int exit_x = 1;
	int exit_y = 2;

	int x = 0;
	int y = 0;
	int exit_found = 0;
	
	
	push(s, start_x, start_y);
	while (!is_empty(s))
	{
		Node *popped = pop(s);
		if (popped != NULL) {
    		x = popped->x;
    		y = popped->y;
		}
		if (in_visited(visited, x, y))
			continue;
		else
		{
			push(visited, x, y);
			if (in_visited(visited, exit_x, exit_y))
			{
				exit_found++;
				break;
			}
			printf("-----------------\n");
			get_next_moves(s, x, y, map);
		}
	}
	
	display_stack(s);
	printf("----------\n");
	display_stack(visited);
	printf("----------\n");
	if (exit_found)
		printf("path to E found!\n");
	else
		printf("path to E was not found!\n");
	free(s);
	free(visited);
	s = NULL;
	visited = NULL;
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
