# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/02 20:50:36 by svilla-d          #+#    #+#              #
#    Updated: 2024/06/22 16:14:53 by svilla-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Settings
UNAME_S := $(shell uname -s)
USER 	:= svilla-d
SRC_DIR	:= src/
OBJ_DIR	:= obj/
BONUS_DIR	  := bonus/
BONUS_OBJ_DIR := bonus_obj/
INCLUDE	:= include
LIBS	:= libs
GRAPH_LIBS 	  := MLX42
GRAPH_INCLUDE := MLX42/include/MLX42
DEBUG_DIR := *.dSYM
LAST_DIR_FILE := obj/.last_dir
LAST_BONUS_DIR_FILE := bonus_obj/.last_dir

TARGET	:= so_long
BONUS	:= so_long_bonus

# CFLAGS 	:= -Wall -Wextra -Werror -g -fsanitize=address -I$(INCLUDE) -Ilibs/$(INCLUDE)
CFLAGS 	:= -Wall -Wextra -Werror -I$(INCLUDE) -Ilibs/$(INCLUDE) -I$(GRAPH_INCLUDE)
ifeq ($(UNAME_S), Linux)
	LDFLAGS	  := -L. -L./$(LIBS) -L./$(GRAPH_LIBS) -L/usr/lib/X11
	MLX_FLAGS := -lmlx42 -lXext -lX11 -ldl -lglfw -pthread -lm -no-pie
else ifeq ($(UNAME_S), Darwin)
	LDFLAGS	  := -L. -L./$(LIBS) -L./$(GRAPH_LIBS)
	MLX_FLAGS := -lmlx42 -framework Cocoa -framework OpenGL -framework IOKit -lglfw
endif
# MLX_FLAGS = -lmlx42 -framework Cocoa -framework OpenGL -framework IOKit -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
LDLIBS	:= -lft

CC 		:= gcc
AR		:= ar -crs
RM		:= rm -f

NAME := libsolong.a
BONUS_NAME := libsolong_bonus.a

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
SRC_FILES	:= map.c utils.c validations.c game.c player.c coin.c path.c move.c
OBJ 		= $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

BONUS_FILES	:= map_bonus.c utils_bonus.c validations_bonus.c enemy_bonus.c \
				game_bonus.c player_bonus.c coin_bonus.c path_bonus.c move_bonus.c
BONUS_OBJ	= $(addprefix $(BONUS_OBJ_DIR), $(BONUS_FILES:.c=.o))

# Message
define PRINT_MESSAGE
	@echo "$1\n*********************************************$(RESET)"
	@echo "$1* $2$(RESET)"
	@echo "$1*********************************************$(RESET)\n"
endef

.PHONY: all clean fclean re tests

all: $(TARGET)
	$(call PRINT_MESSAGE,$(GREEN),"Successful building!!!")

bonus: $(BONUS)
	$(call PRINT_MESSAGE,$(GREEN),"Successful building!!!")

# General Part
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
	@make -C $(GRAPH_LIBS)
	$(call PRINT_MESSAGE,$(CYAN),"Creating library $@...")
	$(AR) $(NAME) $(OBJ)
	@$(RM) $(LAST_DIR_FILE)

# Bonus Part
$(BONUS_OBJ_DIR)%.o: $(BONUS_DIR)%.c
	@mkdir -p $(dir $@)
	@dir=$$(dirname $<); \
    if [ ! -f "$(LAST_BONUS_DIR_FILE)" ] || [ "$$dir" != "$$(cat $(LAST_BONUS_DIR_FILE))" ]; then \
    	echo "$(BLUE)\n*********************************************"; \
		echo "* Compiling $$dir"; \
		echo "*********************************************$(RESET)\n"; \
    	echo "$$dir" > $(LAST_BONUS_DIR_FILE); \
    fi
	$(CC) $(CFLAGS) -c $< -o $@

$(BONUS_NAME): $(BONUS_OBJ)
	@make -C $(LIBS)
	@make -C $(GRAPH_LIBS)
	$(call PRINT_MESSAGE,$(CYAN),"Creating library $@...")
	$(AR) $(BONUS_NAME) $(BONUS_OBJ)
	@$(RM) $(LAST_BONUS_DIR_FILE)
	
clean: 
	$(call PRINT_MESSAGE,$(MAGENTA),"Cleaning temporary files of $(TARGET)...")
	$(RM) -rf $(DEBUG_DIR)
	$(RM) -rf $(OBJ_DIR)
	$(RM) -rf $(BONUS_OBJ_DIR)
	$(RM) $(NAME)
	$(RM) $(BONUS_NAME)
	@make fclean -C $(LIBS)
	@make fclean -C $(GRAPH_LIBS)

fclean:
	$(call PRINT_MESSAGE,$(MAGENTA),"Removing all generated files...")
	$(RM) -rf $(DEBUG_DIR)
	$(RM) -rf $(OBJ_DIR)
	$(RM) -rf $(BONUS_OBJ_DIR)
	$(RM) $(NAME)
	$(RM) $(BONUS_NAME)
	$(RM) $(TARGET)
	$(RM) $(BONUS)
	@make fclean -C $(LIBS)
	@make fclean -C $(GRAPH_LIBS)

re: fclean all

$(TARGET): src/main.c $(NAME)
	$(call PRINT_MESSAGE,$(GREEN),"Generating executable $(TARGET)...")
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) src/main.c $(NAME) $(LDLIBS) $(MLX_FLAGS)

$(BONUS): bonus/main_bonus.c $(BONUS_NAME) 
	$(call PRINT_MESSAGE,$(GREEN),"Generating executable $(BONUS)...")
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(BONUS) bonus/main_bonus.c $(BONUS_NAME) $(LDLIBS) $(MLX_FLAGS)

#compile main.c gcc -o a.out main.c -L. -lft