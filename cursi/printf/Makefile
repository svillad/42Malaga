# Settings
SRC_DIR	:= src/
OBJ_DIR	:= obj/
INCLUDE	:= include
LIBFT	:= libft

CFLAGS 	:= -Wall -Wextra -Werror -I$(INCLUDE)
LDFLAGS	:= -L./$(LIBFT) -L.
LDLIBS	:= -lft -lftprintf
TARGET	:= a.out

CC 		:= gcc
AR		:= ar -crs
RM		:= rm -f

NAME := libftprintf.a

# Files
SRC_FILES	= ft_printf.c
SRC 		= $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ 		= $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

# Define un estilo de mensaje
define PRINT_MESSAGE
	@echo "\n*********************************************"
	@echo "* $1"
	@echo "*********************************************\n"
endef

.PHONY: all clean fclean re

all: $(NAME)
	$(call PRINT_MESSAGE, "Successful building!!!")

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(call PRINT_MESSAGE, "Compiling $<...")
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(call PRINT_MESSAGE, "Creating library $(LIBFT)...")
	@make bonus -C $(LIBFT)
	$(call PRINT_MESSAGE, "Creating library $@...")
	$(AR) $(NAME) $(OBJ)

clean: 
	$(call PRINT_MESSAGE, "Cleaning temporary files...")
	$(RM) -rf $(OBJ_DIR)
	@make clean -C $(LIBFT)

fclean:
	$(call PRINT_MESSAGE, "Removing all generated files...")
	$(RM) -rf $(OBJ_DIR)
	@make fclean -C $(LIBFT)
	$(RM) $(TARGET)
	$(RM) $(NAME)

re: fclean all

$(TARGET): main.c $(NAME)
	$(call PRINT_MESSAGE, "Generating executable $@...")
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)
