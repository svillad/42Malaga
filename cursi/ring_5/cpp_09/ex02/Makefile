# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: svilla-d <svilla-d@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/08 13:30:12 by svilla-d          #+#    #+#              #
#    Updated: 2025/05/24 18:12:20 by svilla-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME   = PmergeMe
CC     = c++
CFLAGS = -Wall -Werror -Wextra -Iincludes -Ilogger -I. -std=c++98 \
        #  -g -fsanitize=address
RM     = rm -rf

# Directories
SRC_DIR         = ./
OBJ_DIR         = obj/
LOGGER_DIR      = logger/

# Source files
MAIN_SRC        = main.cpp
FILES_SRC       = PmergeMe.cpp
FILES_LOGGER    = 

# Full paths
SRC_MAIN        = $(addprefix $(SRC_DIR),$(MAIN_SRC) $(FILES_SRC))
SRC_LOGGER      = $(addprefix $(LOGGER_DIR),$(FILES_LOGGER))
SRC             = $(SRC_MAIN) $(SRC_LOGGER)

# Objects with correct structure in obj/
OBJ_MAIN        = $(SRC_MAIN:$(SRC_DIR)%.cpp=$(OBJ_DIR)%.o)
OBJ_LOGGER      = $(SRC_LOGGER:$(LOGGER_DIR)%.cpp=$(OBJ_DIR)logger/%.o)
OBJ_SRC         = $(OBJ_MAIN) $(OBJ_LOGGER)

# ----------------------------------------------------------------------
#                          Main Compilation
# ----------------------------------------------------------------------

all: $(NAME)

# Compiling individual files
$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling $<"
	$(CC) $(CFLAGS) -c $< -o $@

# Compiling files in `logger/`
$(OBJ_DIR)logger/%.o: $(LOGGER_DIR)%.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling $<"
	$(CC) $(CFLAGS) -c $< -o $@

# Generar ejecutable
$(NAME): $(OBJ_SRC)
	@echo "Linking executable $(NAME)..."
	$(CC) $(CFLAGS) $(OBJ_SRC) -o $@
	@echo "Build complete!"

# ----------------------------------------------------------------------
#                              Clean
# ----------------------------------------------------------------------

clean:
	@echo "Cleaning object files..."
	@$(RM) $(OBJ_DIR) 

fclean: clean
	@echo "Removing binary $(NAME) and logs..."
	@$(RM) $(NAME)
	@$(RM) logs.log
	@$(RM) tests

re: fclean all

# ----------------------------------------------------------------------
#                          Tests Compilation
# ----------------------------------------------------------------------

TESTS_DIR       = ./
MAIN_TESTS	    = main.cpp

# Full paths for tests
SRC_MAIN_TESTS	= $(addprefix $(TESTS_DIR),$(MAIN_TESTS) $(FILES_SRC))
SRC_TESTS		= $(SRC_MAIN_TESTS) $(SRC_LOGGER)
OBJ_MAIN_TESTS	= $(SRC_MAIN_TESTS:$(TESTS_DIR)%.cpp=$(OBJ_DIR)tests/%.o)
OBJ_SRC_TESTS	= $(OBJ_MAIN_TESTS) $(OBJ_LOGGER)

# Compiling test files
$(OBJ_DIR)tests/%.o: $(TESTS_DIR)%.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling test file $<"
	$(CC) $(CFLAGS) -c $< -o $@

# Building and running tests
tests: $(OBJ_SRC_TESTS)
	@echo "Building test executable..."
	$(CC) $(CFLAGS) $(OBJ_SRC_TESTS) -o tests
	@echo "Running tests..."
	- ./tests 3
	- ./tests 5 4
	- ./tests 5 4 9
	- ./tests 3 5 9 7 4
	- ./tests `shuf -i 1-10 -n 10| tr "\n" " "`
	- ./tests `shuf -i 1-100000 -n 3000 | tr "\n" " "`
	- ./tests
	- ./tests 3 3 9 7 4
	- ./tests "-1" "2"
	- ./tests "1" "a"
	- ./tests "99999999999999999999999999999999999" "1"


.PHONY: all clean fclean re tests
