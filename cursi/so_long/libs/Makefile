# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/20 13:18:13 by svilla-d          #+#    #+#              #
#    Updated: 2024/05/20 13:18:21 by svilla-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Settings
SRC_DIR	:= src/
OBJ_DIR	:= obj/
INCLUDE	:= include
LAST_DIR_FILE := obj/.last_dir

CFLAGS 	:= -Wall -Wextra -Werror -I$(INCLUDE)
LDFLAGS	:= -L.
LDLIBS	:= -lft

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

# Source path
LIBFT_DIR			:= libft/
FT_PRINTF_DIR		:= ft_printf/
GET_NEXT_LINE_DIR	:= get_next_line/
PIPEX_DIR			:= pipex/
PUSH_SWAP_DIR		:= push_swap/

# Source files
LIBFT_FILES := ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_isstrempty.c ft_toupper.c ft_tolower.c \
            ft_strlen.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strcmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c \
            ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
            ft_calloc.c ft_strdup.c ft_strndup.c \
            ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
            ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
            ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c \
            ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c
FT_PRINTF_FILES 	:= ft_printf.c ft_printf_int.c ft_printf_hex.c ft_printf_addr.c
GET_NEXT_LINE_FILES := get_next_line.c get_next_line_utils.c
PIPEX_FILES			:= pipex.c pipex_process.c pipex_cmd.c pipex_utils.c
PUSH_SWAP_FILES	:= push_swap.c validations.c validations_utils.c push_swap_utils.c stack_operations.c stack_utils.c \
			node_operations.c sort_operations.c sort_utils.c moves.c operation_swap.c operation_rotate.c \
			operation_reverse_rotate.c operation_utils.c operation_push.c checker.c

# Source complete path
LIBFT_SRC			:= $(addprefix $(SRC_DIR)$(LIBFT_DIR), $(LIBFT_FILES))
FT_PRINTF_SRC		:= $(addprefix $(SRC_DIR)$(FT_PRINTF_DIR), $(FT_PRINTF_FILES))
GET_NEXT_LINE_SRC	:= $(addprefix $(SRC_DIR)$(GET_NEXT_LINE_DIR), $(GET_NEXT_LINE_FILES))
PIPEX_SRC			:= $(addprefix $(SRC_DIR)$(PIPEX_DIR), $(PIPEX_FILES))
PUSH_SWAP_SRC		:= $(addprefix $(SRC_DIR)$(PUSH_SWAP_DIR), $(PUSH_SWAP_FILES))

# All sources files
SRC := $(LIBFT_SRC) $(FT_PRINTF_SRC) $(GET_NEXT_LINE_SRC) $(PIPEX_SRC) $(PUSH_SWAP_SRC)

# All object files
OBJ := $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

# Tests settings
TEST_DIR	:= tests/
TEST_FILES	:= test_ft_printf.c test_get_next_line.c test_pipex.c test_push_swap.c
TEST_NAMES	:= $(basename $(notdir $(TEST_FILES)))
TEST_OUT 	:= $(patsubst %.c, %.out, $(TEST_FILES))
OUTPUT_FILE	:= output.txt

# Message
define PRINT_MESSAGE
	@echo "$1\n*********************************************$(RESET)"
	@echo "$1* $2$(RESET)"
	@echo "$1*********************************************$(RESET)\n"
endef

.PHONY: all clean fclean re tests

all: $(NAME)
	$(call PRINT_MESSAGE,$(GREEN),"Successful building!!!")
	
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@dir=$$(dirname $<); \
    if [ ! -f "$(LAST_DIR_FILE)" ] || [ "$$dir" != "$$(cat $(LAST_DIR_FILE))" ]; then \
    	echo "$(BLUE)\n*********************************************"; \
		echo "* Compiling libs/$$dir"; \
		echo "*********************************************$(RESET)\n"; \
    	echo "$$dir" > $(LAST_DIR_FILE); \
    fi
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(call PRINT_MESSAGE,$(CYAN),"Creating library $@...")
	$(AR) $(NAME) $^
	@$(RM) $(LAST_DIR_FILE)

clean: 
	$(call PRINT_MESSAGE,$(MAGENTA),"Cleaning temporary files of $(NAME)...")
	$(RM) -rf $(OBJ_DIR)
	$(RM) $(TEST_OUT)
	$(RM) $(OUTPUT_FILE)

fclean:
	$(call PRINT_MESSAGE,$(MAGENTA),"Removing all generated files...")
	$(RM) -rf $(OBJ_DIR)
	$(RM) $(TEST_OUT)
	$(RM) $(OUTPUT_FILE)
	$(RM) $(NAME)

re: fclean all

$(TEST_NAMES): %: $(TEST_DIR)%.c $(NAME)
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@.out $^ $(LDLIBS)
	$(call PRINT_MESSAGE,$(GREEN),"Generating executable $(@).out...")
	@./$@.out | cat -e

tests: $(TEST_NAMES)

#compile main.c gcc -o a.out main.c -L. -lft