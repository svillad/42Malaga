# Archivos fuente
SOURCES = main.c file.c utils.c
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
	