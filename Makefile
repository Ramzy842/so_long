#Define the compiler
CC = cc

# Define the flags to pass to the compiler
CFLAGS = -Wall -Wextra -Werror

# Define the source files for the so_long executable
SRC = so_long.c ./src/map.c ./utils/map/map_utils.c ./utils/map/path_checker.c get_next_line.c get_next_line_utils.c

# Define the object files for the so_long executable, generated from the source files
OBJ = $(SRC:.c=.o)

# Define the name of the so_long executable to be generated
NAME = so_long

# Define the default target to be built
all: $(NAME)

# Rule to generate the so_long executable from the object files
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

# Rule to generate the object files from the source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $(patsubst %.c,%.o,$<)

# Clean target to remove generated files
clean:
	rm -f $(OBJ) map_utils.o map.o

# Fclean target to remove executable files and perform clean
fclean: clean
	rm -f $(NAME)

# Re target to rebuild the project from scratch
re: fclean all

.PHONY: all clean fclean
