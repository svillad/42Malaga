# Archivos fuente
SOURCES	= ft_isalpha.c
OBJECTS	= $(SOURCES:.c=.o)
CFLAGS 	= -Wall -Wextra -Werror
CC 		= gcc

NAME = libft.a

.PHONY: all clean fclean re

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)

clean: 
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

gcc -o test_ft_isalpha main.c test_ft_isalpha.c ../ft_isalpha.c -I. -I./tests
./test_ft_isalpha