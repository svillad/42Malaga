# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/02 20:50:36 by svilla-d          #+#    #+#              #
#    Updated: 2024/05/04 17:34:29 by svilla-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Settings
USER 	:= svilla-d
SRC_DIR	:= src/
OBJ_DIR	:= obj/
INCLUDE	:= include
LIBS	:= libs
GRAPH_LIBS 	  := MLX42
GRAPH_INCLUDE := MLX42/include/MLX42
DEBUG_DIR := *.dSYM
LAST_DIR_FILE := obj/.last_dir

TARGET	:= so_long
BONUS	:= checker

# CFLAGS 	:= -Wall -Wextra -Werror -g -fsanitize=address -I$(INCLUDE) -Ilibs/$(INCLUDE)
CFLAGS 	:= -Wall -Wextra -Werror -I$(INCLUDE) -Ilibs/$(INCLUDE) -I$(GRAPH_INCLUDE)
LDFLAGS	:= -L./$(LIBS) -L. -L./$(GRAPH_LIBS)
MLX_FLAGS = -lmlx42 -framework Cocoa -framework OpenGL -framework IOKit -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
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
	@make -C $(GRAPH_LIBS)
	$(call PRINT_MESSAGE,$(CYAN),"Creating library $@...")
	$(AR) $(NAME) $(OBJ)
	@$(RM) $(LAST_DIR_FILE)
	
clean: 
	$(call PRINT_MESSAGE,$(MAGENTA),"Cleaning temporary files of $(TARGET)...")
	$(RM) -rf $(DEBUG_DIR)
	$(RM) -rf $(OBJ_DIR)
	$(RM) $(NAME)
	@make fclean -C $(LIBS)
	@make fclean -C $(GRAPH_LIBS)

fclean:
	$(call PRINT_MESSAGE,$(MAGENTA),"Removing all generated files...")
	$(RM) -rf $(DEBUG_DIR)
	$(RM) -rf $(OBJ_DIR)
	$(RM) $(NAME)
	$(RM) $(TARGET)
	$(RM) $(BONUS)
	@make fclean -C $(LIBS)
	@make fclean -C $(GRAPH_LIBS)

re: fclean all

$(TARGET): src/main.c $(NAME)
	$(call PRINT_MESSAGE,$(GREEN),"Generating executable $(TARGET)...")
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) src/main.c $(NAME) $(LDLIBS) $(MLX_FLAGS)

bonus: src/bonus.c $(NAME) $(TARGET)
	$(call PRINT_MESSAGE,$(GREEN),"Generating executable $(BONUS)...")
	$(CC) $(CFLAGS) $(LDFLAGS) -o checker src/bonus.c $(NAME) $(LDLIBS) $(MLX_FLAGS)

#compile main.c gcc -o a.out main.c -L. -lft