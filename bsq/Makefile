# Archivos fuente
SOURCES = main.c ft_file.c ft_utils.c ft_line_one.c ft_prints.c ft_get_sizes.c ft_square.c ft_map.c ft_case_n.c
OBJECTS = $(SOURCES:.c=.o)
CFLAGS = -Wall -Wextra -Werror

NAME = bsq

.PHONY: clean fclean

all: $(NAME)

%.o: %.c
	cc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	cc $(CFLAGS) $(OBJECTS) -o $(NAME)

clean: 
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all
	