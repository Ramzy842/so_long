/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchahban <rchahban@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 19:49:38 by rchahban          #+#    #+#             */
/*   Updated: 2023/03/26 21:00:20 by rchahban         ###   ########.fr       */
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
			//printf("* map is not rectangular\n");
			return (0);
		}
		x++;
	}
	// printf("* map is rectangular\n");
	return (1);
}

/* 4 - The map must be closed/surrounded by walls. 
		If it’s not, the program must return
		an error. */

int		map_surrounded_by_walls(char **map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	// check that first line is all filled with '1's
	while (x < 1)
	{
		while (map[x][y] && map[x][y] != '\n')
		{
			if (map[x][y] != WALL)
			{
				//printf("first line isn't surrounded with walls\n");
				return (0);
			}
			y++;
		}
		x++;
	}
	// check that the last line is all filled with '1's
	x = 0;
	y = 0;
	while (x < 1)
	{
		while (map[ft_strlen_2d(map) - 1][y] && map[ft_strlen_2d(map) - 1][y] != '\0')
		{
			if (map[ft_strlen_2d(map) - 1][y] != WALL)
			{
				//printf("last line isn't surrounded with walls\n");
				return (0);
			}
			y++;
		}
		x++;
	}
	// check that the lines in between start and end with '1'
	x = 1;
	while (x < ft_strlen_2d(map) - 1)
	{
		if (map[x][0] != WALL || map[x][ft_strlen(map[x]) - 2] != WALL )
		{
			//printf("the line %d is not surrounded by walls\n", x + 1);
			return (0);
		}
		x++;
	}
	return (1);
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

void get_next_moves(Stack *s, int a, int b, char **map, int rows, int cols)
{
	if (a > 0 && map[a - 1][b] != WALL)
		push(s, a - 1, b);
	if (b < cols && map[a][b + 1] != WALL)
		push(s, a, b + 1);
	if (a < rows && map[a + 1][b] != WALL)
		push(s, a + 1, b);
	if (b > 0 && map[a][b - 1] != WALL)
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
	//printf("popped [%d][%d]\n", temp->x, temp->y);
	return temp;
}

void peek(Stack *stack)
{
	if (is_empty(stack))
		printf("Stack is empty!\n");
	else
		printf("top value is: [%d][%d]\n", stack->top->x, stack->top->y);
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
		// printf("Visited Stack is Empty!\n");
		return (0);
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

int count_collectibles(char **map)
{
	int	x;
	int	y;
	int	collectibles;

	x = 0;
	y = 0;
	collectibles = 0;
	while(map[x])
	{
		y = 0;
		while(map[x][y])
		{
			if (map[x][y] == COLLECTIBLE)
				collectibles++;
			y++;
		}
		x++;
	}
	return (collectibles);
}

int	path_is_valid(char **map)
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
	Stack *collectibles_stack = create_stack();

	int start_x;
	int start_y;
	int exit_x;
	int exit_y;
	int rows;
	int cols;
	
	rows = ft_strlen_2d(map);
	cols = ft_strlen(map[0]) - 1;
	
	int m;
	int n;
	
	m = 0;
	while(map[m] != NULL)
	{
		n = 0;
		while (map[m][n] != '\0')
		{
			if(map[m][n] == 'P')
			{
				start_x = m;
				start_y = n;
			}
			if(map[m][n] == 'E')
			{
				exit_x = m;
				exit_y = n;
			}
			n++;
		}
		m++;
	}
	// Part 1: Exit detection
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
			//printf("-----------------\n");
			get_next_moves(s, x, y, map, rows, cols);
		}
	}

	free(visited);
	visited = NULL;
	visited = create_stack();

	// Part 2: Collectibles detection
	x = 0;
	y = 0;
	int number_of_collectibles = 0;
	int collectibles_found = 0;
	
	m = 0;
	push(collectibles_stack, start_x, start_y);
	while(map[m] != NULL)
	{
		n = 0;
		while (map[m][n] != '\0')
		{
			if(map[m][n] == COLLECTIBLE)
			{
				number_of_collectibles++;
			}
			n++;
		}
		m++;
	}
		while (!is_empty(collectibles_stack))
		{
			Node *popped = pop(collectibles_stack);
			if (popped != NULL) {
    			x = popped->x;
    			y = popped->y;
			}
			if (in_visited(visited, x, y))
				continue;
			else
			{
				push(visited, x, y);
				if (in_visited(visited, x, y) && map[x][y] == COLLECTIBLE)
					collectibles_found++;
				if (collectibles_found == number_of_collectibles)
					break;
				//printf("-----------------\n");
				get_next_moves(collectibles_stack, x, y, map, rows, cols);
			}
		}
	
	
	//printf("* collectibles found: %d\n", collectibles_found);
	//printf("* number of collectibles: %d\n", number_of_collectibles);
	//display_stack(s);
	//printf("----------\n");
	//display_stack(visited);
	//printf("----------\n");
	free(s);
	free(visited);
	free(collectibles_stack);
	s = NULL;
	visited = NULL;
	collectibles_stack = NULL;
	if (exit_found && number_of_collectibles == collectibles_found)
		// printf("* Path is Valid!\n");
		return (1);
	else
		//printf("* Path is not Valid!\n");
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
