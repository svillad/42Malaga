# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/07 11:03:31 by svilla-d          #+#    #+#              #
#    Updated: 2023/10/07 11:03:36 by svilla-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Archivos fuente
SOURCES	=  \
		ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c \
		ft_strlen.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c \
		ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
		ft_calloc.c ft_strdup.c \
		ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
BONUS = \
		ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c \
		ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

OBJECTS		  = $(SOURCES:.c=.o)
BONUS_OBJECTS = $(BONUS:.c=.o)
HEADERS = libft.h

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

bonus: $(OBJECTS) $(BONUS_OBJECTS) $(HEADERS)
	$(AR) $(NAME) $(OBJECTS) $(BONUS_OBJECTS)

clean: 
	rm -f $(OBJECTS) $(BONUS_OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

#compile main.c gcc -o a.out main.c -L. -lft