# Archivos fuente
SOURCES	= 	\
		ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c \
		ft_strlen.c ft_strchr.c ft_strrchr.c
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