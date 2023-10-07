# Archivos fuente
SOURCES	=  \
		ft_printf.c

OBJECTS	= $(SOURCES:.c=.o)
HEADERS = ft_printf.h

CFLAGS 	= -Wall -Wextra -Werror
CC 		= gcc
AR		= ar -crs

NAME = libft.a

.PHONY: all clean fclean re bonus

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS) $(HEADERS)
	$(AR) $(NAME) $(OBJECTS)

clean: 
	rm -f $(OBJECTS) $(BONUS_OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

#compile main.c gcc -o a.out main.c -L. -lft