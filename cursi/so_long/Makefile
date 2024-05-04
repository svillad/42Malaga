# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/02 20:50:36 by svilla-d          #+#    #+#              #
#    Updated: 2024/05/02 20:53:50 by svilla-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Settings
SRC_DIR	:= src/
OBJ_DIR	:= obj/
INCLUDE	:= include
LIBS	:= libs
DEBUG_DIR := *.dSYM
LAST_DIR_FILE := obj/.last_dir

TARGET	:= so_long
BONUS	:= checker
# CFLAGS 	:= -Wall -Wextra -Werror -g -fsanitize=address -I$(INCLUDE) -Ilibs/$(INCLUDE)
CFLAGS 	:= -Wall -Wextra -Werror -I$(INCLUDE) -Ilibs/$(INCLUDE) -I/opt/X11/include -Imlx
LDFLAGS	:= -L./$(LIBS) -L.
MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
LDLIBS	:= -lft

CC 		:= gcc
AR		:= ar -crs
RM		:= rm -f

NAME := libsolong.a

# Colors
RESET   = \033[0m
RED     = \033[31m
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE    = \033[34m
MAGENTA = \033[35m
CYAN    = \033[36m
WHITE   = \033[37m

# Files
SRC_FILES	:= test.c
SRC 		= $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ 		= $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

# Message
define PRINT_MESSAGE
	@echo "$1\n*********************************************$(RESET)"
	@echo "$1* $2$(RESET)"
	@echo "$1*********************************************$(RESET)\n"
endef

.PHONY: all clean fclean re tests

all: $(TARGET)
	$(call PRINT_MESSAGE,$(GREEN),"Successful building!!!")

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@dir=$$(dirname $<); \
    if [ ! -f "$(LAST_DIR_FILE)" ] || [ "$$dir" != "$$(cat $(LAST_DIR_FILE))" ]; then \
    	echo "$(BLUE)\n*********************************************"; \
		echo "* Compiling $$dir"; \
		echo "*********************************************$(RESET)\n"; \
    	echo "$$dir" > $(LAST_DIR_FILE); \
    fi
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@make -C $(LIBS)
	$(call PRINT_MESSAGE,$(CYAN),"Creating library $@...")
	$(AR) $(NAME) $(OBJ)
	@$(RM) $(LAST_DIR_FILE)
	
clean: 
	$(call PRINT_MESSAGE,$(MAGENTA),"Cleaning temporary files of $(TARGET)...")
	$(RM) -rf $(DEBUG_DIR)
	$(RM) -rf $(OBJ_DIR)
	$(RM) $(NAME)
	@make fclean -C $(LIBS)

fclean:
	$(call PRINT_MESSAGE,$(MAGENTA),"Removing all generated files...")
	$(RM) -rf $(DEBUG_DIR)
	$(RM) -rf $(OBJ_DIR)
	$(RM) $(NAME)
	$(RM) $(TARGET)
	$(RM) $(BONUS)
	@make fclean -C $(LIBS)

re: fclean all

$(TARGET): src/main.c $(NAME)
	$(call PRINT_MESSAGE,$(GREEN),"Generating executable $(TARGET)...")
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) src/main.c $(NAME) $(LDLIBS) $(MLX_FLAGS)

bonus: src/bonus.c $(NAME) $(TARGET)
	$(call PRINT_MESSAGE,$(GREEN),"Generating executable $(BONUS)...")
	$(CC) $(CFLAGS) $(LDFLAGS) -o checker src/bonus.c $(NAME) $(LDLIBS) $(MLX_FLAGS)

#compile main.c gcc -o a.out main.c -L. -lft