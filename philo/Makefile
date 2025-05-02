NAME = philo

# Directory
INC = -I ./include/
OBJ_DIR = obj/

#complier 
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf

SRCBASE = main free init parsing
SRC = $(addsuffix .c, $(addprefix srcs/, $(SRCBASE)))

OBJ = $(SRC:srcs/%.c=$(OBJ_DIR)%.o)

start:
	@make all

#ensure directories exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Build Executable
all: $(NAME)
	@echo "\033[32m[Program is ready for use]\033[0m"

$(NAME): $(OBJ_DIR) $(OBJ)
	@$(CC) $(CFLAGS) $(INC) $(OBJ) -o $(NAME)

# Rule to compile object files
$(OBJ_DIR)%.o: srcs/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean: 
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: start all clean fclean re

