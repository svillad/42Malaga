# Archivos fuente
SOURCES = main.c file.c utils.c
OBJECTS = $(SOURCES:.c=.o)
CFLAGS = -Wall -Wextra -Werror

NAME = bsq

.PHONY: clean fclean

all: $(NAME)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	gcc $(CFLAGS) $(OBJECTS) -o $(NAME)

clean: 
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)
