#COLORS
GREEN = \e[0;32m
BLUE = \e[1;034m
RED = \e[0;31m
MAGENTA = \033[1;35m
ORANGE = \033[1;38;5;208m
GREY = \033[0;37m
CYAN = \e[1;36m
RESET = \e[0m

#COMMANDS
MAKEC = make -C
MAKECLEANC = make clean -C
RM = rm -rf

#PROJECT
NAME = philo
OBJ_DIR = ./objs/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
SRC_DIR = ./source/

SRC = parsing.c init.c threads.c routine.c utils.c monitoring.c

#COMPILATION
CC = cc #-fsanitize=thread
GCC = cc -g
CFLAGS = -Wall -Wextra -Werror -pthread

#RULES
all : $(NAME)

$(NAME) : $(OBJ)
	@echo "$(CYAN)[!]$(RESET) Working on project ... "
	$(GCC) $(CFLAGS) $(OBJ) $(SRC_DIR)main.c -o $(NAME)
	@echo "$(GREEN)[✔] PHILO ready!$(RESET)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
#	@echo "$(CYAN)[!]$(RESET) Creating object $@ ..."
	mkdir -p $(dir $@)
	$(GCC) $(CFLAGS) -c $< -o $@

clean :
	@echo "$(CYAN)[!]$(RESET) Executing cleaning ..."
	$(RM) $(OBJ_DIR) > /dev/null 2>&1
	$(RM) $(BONUS_OBJ_DIR) > /dev/null 2>&1
	@echo "$(RED)[✔] Cleaned!$(RESET) "

fclean :
	@echo "$(CYAN)[!]$(RESET) Executing full cleaning..."
	$(RM) $(NAME) $(OBJ_DIR)
	$(RM) $(BONUS_NAME) $(BONUS_OBJ_DIR)
#	$(RM) library/minilibx-linux
	@echo "$(RED)[✔] Full cleaning!$(RESET) "

re : fclean all
	#@echo "$(GREEN)[✔]$(RESET) $(MAGENTA)Refresh Ok!$(RESET) "


.SILENT:
.PHONY: all clean fclean re
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
#                NOTES AND REMINDERS            #
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
#          $< represent the prerequisite        #
#          $@ represent the target              #
# mkdir -p make parent directory without errors #
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#