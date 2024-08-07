# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/07 14:11:56 by svilla-d          #+#    #+#              #
#    Updated: 2024/07/10 14:10:01 by svilla-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Settings
UNAME_S := $(shell uname -s)
USER 	:= svilla-d

DIR				:= philo
NAME			:= $(DIR)/libphilo.a
SRC_DIR			:= $(DIR)/src/
OBJ_DIR			:= $(DIR)/obj/
INCLUDE			:= $(DIR)/include
LAST_DIR_FILE	:= $(DIR)/obj/.last_dir
DEBUG_DIR 		:= $(DIR)/*.dSYM
TARGET			:= $(DIR)/philo

BONUS_DIR		:= philo_bonus
BONUS_NAME		:= $(BONUS_DIR)/libphilo_bonus.a
BONUS_SRC_DIR	:= $(BONUS_DIR)/src/
BONUS_OBJ_DIR	:= $(BONUS_DIR)/obj/
BONUS_INCLUDE	:= $(BONUS_DIR)/include/
BONUS_LAST_DIR_FILE := $(BONUS_DIR)/obj/.last_dir
BONUS_DEBUG_DIR	:= $(BONUS_DIR)/*.dSYM
BONUS_TARGET	:= $(BONUS_DIR)/philo_bonus


# CFLAGS 	:= -Wall -Wextra -Werror -g -fsanitize=address -I$(INCLUDE) -Ilibs/$(INCLUDE)
CFLAGS 	:= -Wall -Wextra -Werror -I$(INCLUDE) -I$(BONUS_INCLUDE) -pthread
LDFLAGS	:= -L. -lpthread
CC 		:= gcc
AR		:= ar -crs
RM		:= rm -f

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
SRC_FILES	:= table.c utils.c validations.c philosopher.c mutex.c forks.c actions.c
OBJ 		= $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

BONUS_FILES	:= table_bonus.c utils_bonus.c validations_bonus.c philosopher_bonus.c \
			semaphore_bonus.c forks_bonus.c actions_bonus.c
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

bonus: $(BONUS_TARGET)
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
	$(call PRINT_MESSAGE,$(CYAN),"Creating library $@...")
	$(AR) $(NAME) $(OBJ)
	@$(RM) $(LAST_DIR_FILE)

# Bonus Part
$(BONUS_OBJ_DIR)%.o: $(BONUS_SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@dir=$$(dirname $<); \
    if [ ! -f "$(BONUS_LAST_DIR_FILE)" ] || [ "$$dir" != "$$(cat $(BONUS_LAST_DIR_FILE))" ]; then \
    	echo "$(BLUE)\n*********************************************"; \
		echo "* Compiling $$dir"; \
		echo "*********************************************$(RESET)\n"; \
    	echo "$$dir" > $(BONUS_LAST_DIR_FILE); \
    fi
	$(CC) $(CFLAGS) -c $< -o $@

$(BONUS_NAME): $(BONUS_OBJ)
	$(call PRINT_MESSAGE,$(CYAN),"Creating library $@...")
	$(AR) $(BONUS_NAME) $(BONUS_OBJ)
	@$(RM) $(BONUS_LAST_DIR_FILE)
	
clean: 
	$(call PRINT_MESSAGE,$(MAGENTA),"Cleaning temporary files of $(TARGET)...")
	$(RM) -r $(DEBUG_DIR)
	$(RM) -r $(BONUS_DEBUG_DIR)
	$(RM) -r $(OBJ_DIR)
	$(RM) -r $(BONUS_OBJ_DIR)
	$(RM) $(NAME)
	$(RM) $(BONUS_NAME)

fclean:
	$(call PRINT_MESSAGE,$(MAGENTA),"Removing all generated files...")
	$(RM) -r $(DEBUG_DIR)
	$(RM) -r $(BONUS_DEBUG_DIR)
	$(RM) -r $(OBJ_DIR)
	$(RM) -r $(BONUS_OBJ_DIR)
	$(RM) $(NAME)
	$(RM) $(BONUS_NAME)
	$(RM) $(TARGET)
	$(RM) $(BONUS_TARGET)

re: fclean all

$(TARGET): $(SRC_DIR)main.c $(NAME)
	$(call PRINT_MESSAGE,$(GREEN),"Generating executable $(TARGET)...")
	$(CC) -o $(TARGET) $(SRC_DIR)main.c $(CFLAGS) $(LDFLAGS) $(NAME)
	
$(BONUS_TARGET): $(BONUS_SRC_DIR)main_bonus.c $(BONUS_NAME) 
	$(call PRINT_MESSAGE,$(GREEN),"Generating executable $(BONUS_TARGET)...")
	$(CC) -o $(BONUS_TARGET) $(BONUS_SRC_DIR)main_bonus.c $(CFLAGS) $(LDFLAGS) $(BONUS_NAME)

#compile main.c: gcc -o a.out main.c -L. -lft