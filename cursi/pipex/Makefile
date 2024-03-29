# Settings
SRC_DIR	:= src/
OBJ_DIR	:= obj/
INCLUDE	:= include
LIBS	:= libs
DEBUG_DIR := pipex.dSYM

CFLAGS_FILE := obj/.cflags.txt
CFLAGS 	:= -Wall -Wextra -Werror -g -fsanitize=address -I$(INCLUDE) -Ilibs/$(INCLUDE)
LDFLAGS	:= -L./$(LIBS) -L.
LDLIBS	:= -lft
TARGET	:= pipex

CC 		:= gcc
AR		:= ar -crs
RM		:= rm -f

NAME := libpipex.a

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
SRC_FILES	= pipex.c pipex_cmd.c pipex_utils.c
SRC 		= $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ 		= $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

# Message format
define PRINT_MESSAGE
	@echo "$1\n*********************************************$(RESET)"
	@echo "$1* $2$(RESET)"
	@echo "$1*********************************************$(RESET)\n"
endef

.PHONY: all clean fclean re bonus FORCE

all: $(TARGET)
	$(call PRINT_MESSAGE, $(GREEN), "Successful!!!")

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
	
$(NAME): $(OBJ)
	$(call PRINT_MESSAGE,$(CYAN),"Compiling library files of $(LIBS)...")
	@make -C $(LIBS)
	$(call PRINT_MESSAGE,$(CYAN),"Creating library $@...")
	$(AR) $(NAME) $(OBJ)

clean: 
	$(call PRINT_MESSAGE, $(MAGENTA), "Cleaning temporary files of $(TARGET)...")
	$(RM) -rf $(DEBUG_DIR)
	$(RM) -rf $(OBJ_DIR)
	$(RM) $(NAME)
	@make clean -C $(LIBS)

fclean:
	$(call PRINT_MESSAGE, $(MAGENTA), "Removing all generated files...")
	$(RM) -rf $(DEBUG_DIR)
	$(RM) -rf $(OBJ_DIR)
	$(RM) $(NAME)
	$(RM) $(TARGET)
	@make fclean -C $(LIBS)

re: fclean all

$(TARGET): main.c $(NAME) $(CFLAGS_FILE)
	$(call PRINT_MESSAGE, $(GREEN), "Generating executable $(TARGET)...")
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) main.c libpipex.a $(LDLIBS)
	
bonus: CFLAGS += -DBONUS
bonus: $(TARGET)
	$(call PRINT_MESSAGE, $(GREEN), "Successful!!!")
	
$(CFLAGS_FILE): FORCE
	@echo "$(CFLAGS)" | cmp -s - $@ || echo "$(CFLAGS)" > $@

FORCE:
# bonus: main.c $(NAME)
# 	$(call PRINT_MESSAGE, $(GREEN), "Generating executable $(TARGET)...")
# 	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $^ $(LDLIBS)

#compile main.c gcc -o a.out main.c -L. -lft