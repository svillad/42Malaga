# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/07 11:03:31 by svilla-d          #+#    #+#              #
#    Updated: 2024/03/06 11:49:21 by svilla-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Settings
SRC_DIR	:= src/
OBJ_DIR	:= obj/
INCLUDE	:= include

CFLAGS 	:= -Wall -Wextra -Werror -I$(INCLUDE)
LDFLAGS	:= -L.
LDLIBS	:= 
TARGET	:= test.out

CC 		:= gcc
AR		:= ar -crs
RM		:= rm -f

NAME := libft.a

# Colors
RESET   = \033[0m
RED     = \033[31m
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE    = \033[34m
MAGENTA = \033[35m
CYAN    = \033[36m
WHITE   = \033[37m


# Order
SRC_FILES	=  \
			ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c \
			ft_strlen.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strcmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c \
			ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
			ft_calloc.c ft_strdup.c \
			ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c \
			ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c \
			ft_printf.c ft_printf_int.c ft_printf_hex.c ft_printf_addr.c \
			get_next_line.c get_next_line_utils.c

SRC 		= $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ 		= $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

# Define un estilo de mensaje
define PRINT_MESSAGE
	@echo "$1\n*********************************************$(RESET)"
	@echo "$1* $2$(RESET)"
	@echo "$1*********************************************$(RESET)\n"
endef

.PHONY: all clean fclean re

all: $(NAME)
	$(call PRINT_MESSAGE, $(GREEN), "Successful building!!!")

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(call PRINT_MESSAGE,$(CYAN),"Creating library $@...")
	$(AR) $(NAME) $^

clean: 
	$(call PRINT_MESSAGE, $(MAGENTA), "Cleaning temporary files of $(NAME)...")
	$(RM) -rf $(OBJ_DIR)
	$(RM) $(TARGET)

fclean:
	$(call PRINT_MESSAGE, $(MAGENTA), "Removing all generated files...")
	$(RM) -rf $(OBJ_DIR)
	$(RM) $(TARGET)
	$(RM) $(NAME)

re: fclean all

test: tests/test_lib.c $(NAME)
	$(call PRINT_MESSAGE, $(GREEN), "Generating executable $(TARGET)...")
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $^ $(LDLIBS)
	./$(TARGET) | cat -e

#compile main.c gcc -o a.out main.c -L. -lft