# Directorio de la librería (ajústalo según tu estructura)
LIBFT_DIR = ../

# Fuentes y objetos
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)

# Compilador y opciones de compilación
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR) -I.

# Nombre del ejecutable
NAME = test.out

.PHONY: all clean fclean re

all: lib $(NAME) clean

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ -L$(LIBFT_DIR) -lft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: cleanlib
	rm -f $(OBJECTS)

fclean: fcleanlib clean
	rm -f $(NAME)

re: fclean lib all

lib:
	make -C .. re

cleanlib:
	make -C .. clean

fcleanlib:
	make -C .. fclean

# gcc -o test_ft_isalpha main.c test_ft_isalpha.c ../ft_isalpha.c -I. -I./tests
# ./test_ft_isalpha