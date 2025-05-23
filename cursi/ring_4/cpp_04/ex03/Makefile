# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/08 13:30:12 by svilla-d          #+#    #+#              #
#    Updated: 2025/01/25 18:55:44 by svilla-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME            = character

CC              = c++

# Logging levels:
# 0 - DEBUG: Detailed debug information.
# 1 - INFO: General information about program execution.
# 2 - WARN: Indications of potential issues.
# 3 - ERROR: Errors that affect program execution.
# 4 - OFF: Disable all logging.
LOG		 		?= 4
CFLAGS          = -Wall -Werror -Wextra -Iincludes -I. -std=c++98 -DLOG=$(LOG) -g -fsanitize=address 

RM              = rm -rf

SRC_DIR         = ./
OBJ_DIR         = obj/

FILES_SRC       = main.cpp
FILES_EXEC      = AMateria.cpp Ice.cpp Cure.cpp Character.cpp MateriaSource.cpp Logger.cpp

SRC_MAIN        = $(addprefix $(SRC_DIR),$(FILES_SRC))
SRC_EXEC        = $(addprefix $(SRC_DIR),$(FILES_EXEC))
SRC             = $(SRC_MAIN) $(SRC_EXEC)

OBJ_MAIN        = $(SRC_MAIN:$(SRC_DIR)%.cpp=$(OBJ_DIR)%.o)
OBJ_EXEC        = $(SRC_EXEC:$(SRC_DIR)%.cpp=$(OBJ_DIR)%.o)
OBJ_SRC         = $(OBJ_MAIN) $(OBJ_EXEC)

all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ 

$(NAME): $(OBJ_SRC)
	$(CC) $(CFLAGS) $(OBJ_SRC) -o $@

clean:
	@$(RM) $(OBJ_DIR) 

fclean: clean
	@$(RM) $(NAME)
	@$(RM) tests

re: fclean all

# --------------------------------------------------
#             Test compilation process             |
# --------------------------------------------------

TESTS_DIR         = ./
FILES_SRC_TESTS	= test.cpp

SRC_MAIN_TESTS	= $(addprefix $(TESTS_DIR),$(FILES_SRC_TESTS))
SRC_TESTS		= $(SRC_MAIN_TESTS) $(SRC_EXEC)
OBJ_MAIN_TESTS	= $(SRC_MAIN_TESTS:$(TESTS_DIR)%.cpp=$(OBJ_DIR)%.o)
OBJ_SRC_TESTS	= $(OBJ_MAIN_TESTS) $(OBJ_EXEC)

$(OBJ_DIR)%.o: $(TESTS_DIR)%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

tests: $(OBJ_SRC_TESTS)
	$(CC) $(CFLAGS) $(OBJ_SRC_TESTS) -o $@
	./tests

.PHONY: all clean fclean re tests
