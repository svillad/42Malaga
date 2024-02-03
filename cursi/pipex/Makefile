# Settings
SRC_DIR	:= src/
OBJ_DIR	:= obj/
INCLUDE	:= include
LIBS	:= libs

CFLAGS 	:= -Wall -Wextra -Werror -I$(INCLUDE)
LDFLAGS	:= -L./$(LIBS) -L.
LDLIBS	:= -lft -lftprintf
TARGET	:= pipex

CC 		:= gcc
AR		:= ar -crs
RM		:= rm -f

NAME := libftprintf.a

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
SRC_FILES	= pipex.c
SRC 		= $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ 		= $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

# Message format
define PRINT_MESSAGE
	@echo "$1\n*********************************************$(RESET)"
	@echo "$1* $2$(RESET)"
	@echo "$1*********************************************$(RESET)\n"
endef

.PHONY: all clean fclean re


.PHONY: all clean fclean re

all: $(TARGET)
	$(call PRINT_MESSAGE, $(GREEN), "Successful!!!")

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
	
$(NAME): $(OBJ)
	$(call PRINT_MESSAGE,$(CYAN),"Compiling library files of $(LIBS)...")
	@make -C $(LIBS)
	@cp libs/libft.a .
	@mv libft.a $(NAME)
	$(call PRINT_MESSAGE,$(CYAN),"Creating library $@...")
	$(AR) $(NAME) $(OBJ)

clean: 
	$(call PRINT_MESSAGE, $(MAGENTA), "Cleaning temporary files...")
	$(RM) $(TARGET)
	$(RM) -rf $(OBJ_DIR)
	@make clean -C $(LIBS)

fclean:
	$(call PRINT_MESSAGE, $(MAGENTA), "Removing all generated files...")
	$(RM) -rf $(OBJ_DIR)
	@make fclean -C $(LIBS)
	$(RM) $(TARGET)
	$(RM) $(NAME)

re: fclean all

$(TARGET): main.c $(NAME)
	$(call PRINT_MESSAGE, $(GREEN), "Generating executable $(TARGET)...")
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $^ $(LDLIBS)

#compile main.c gcc -o a.out main.c -L. -lft