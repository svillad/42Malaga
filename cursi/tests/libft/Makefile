# Directorio de la librería (ajústalo según tu estructura)
LIBFT_DIR = ../../libft

# Fuentes y objetos
SOURCES = main.c test_ft_isalpha.c ft_isalpha.c
OBJECTS = $(SOURCES:.c=.o)

# Compilador y opciones de compilación
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR) -I. # Agrega -I. para incluir el directorio actual

# Nombre del ejecutable
NAME = test.out

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ -L$(LIBFT_DIR) -lft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

path: 
	ls $(LIBFT_DIR)