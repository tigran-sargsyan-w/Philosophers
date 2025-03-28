# **************************************************************************** #
#                                  Makefile                                    #
# **************************************************************************** #

NAME        = philo

# -------------------------------
#   Compiler and Flags
# -------------------------------
CC          = cc -pthread
C_FLAGS     = -Wall -Wextra -Werror -g
INC_FLAGS   = -I$(INC_DIR)

# -------------------------------
#   Directories
# -------------------------------
SRC_DIR     = src
INC_DIR     = includes
OBJ_DIR     = obj

# -------------------------------
#   All Source Files 
# -------------------------------
SRCS        = $(SRC_DIR)/main.c \
			$(SRC_DIR)/exit_utils.c \
			$(SRC_DIR)/parsing.c

# -------------------------------
#   Header Files
# -------------------------------
HEADERS     = $(INC_DIR)/philo.h

# -------------------------------
#   Object & Dependency Files
# -------------------------------
OBJS        = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

DEPS 		= $(OBJS:%.o=%.d)

# **************************************************************************** #
#                                 Build Rules                                  #
# **************************************************************************** #

all: $(NAME)
	@echo "🚀 Executable $(NAME) created successfully!"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME)
	@echo "✅ $(NAME) compiled."

bonus: all

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	@$(CC) $(C_FLAGS) $(INC_FLAGS) -MMD -MP -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "🗑️ $(NAME) object files removed."

fclean:
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME) 
	@echo "😒 $(NAME) and $(NAME) object files removed."

re: fclean all

-include $(DEPS)
.PHONY: all bonus clean fclean re
.DELETE_ON_ERROR: