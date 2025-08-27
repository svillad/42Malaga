
NAME            = ircserv

CC              = c++
CFLAGS 			= -Wall -Wextra -Werror -std=c++98 -Iincludes -g
RM              = rm -rf

SRC_DIR         = src/
OBJ_DIR         = obj/

FILES_SRC       = main.cpp Server.cpp Client.cpp CliCmdHandler.cpp \
				Channel.cpp CmdRegister.cpp CmdJoin.cpp CmdPrivmsg.cpp \
				CmdKick.cpp CmdInvite.cpp CmdTopic.cpp CmdMode.cpp \
				CmdList.cpp CmdWhois.cpp CmdWho.cpp CmdNames.cpp \
				CmdBot.cpp CmdHelp.cpp BotClient.cpp Game.cpp \
				DccProxy.cpp TransferHandler.cpp

SRC             = $(addprefix $(SRC_DIR),$(FILES_SRC))
OBJ_SRC         = $(addprefix $(OBJ_DIR), $(FILES_SRC:.cpp=.o))

HEADERS 		= include/Server.hpp include/Client.hpp include/CliCmdHandler.hpp \
				include/Channel.hpp
INCLUDES 		= -I ./include

GREEN           = \033[0;32m
RED             = \033[0;31m
YELLOW          = \033[1;33m
BLUE            = \033[1;34m
BOLD 			= \033[1m
END             = \033[0m

vpath %.cpp $(SRC_DIR)

all: $(NAME)

$(OBJ_DIR)%.o: %.cpp
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(BLUE)Compiled$(END): $<"

$(NAME): $(HEADERS) $(OBJ_SRC)
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJ_SRC) -o $(NAME)
	@echo "$(BOLD)$(GREEN)Executable $(NAME) created successfully!$(END)"

clean:
	@$(RM) $(OBJ_DIR)
	@echo "$(YELLOW)Object files removed$(END)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(BOLD)$(RED)Executable $(NAME) removed$(END)"

re: fclean all

.PHONY: all clean fclean re
