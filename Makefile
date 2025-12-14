NAME        = minishell
CC          = cc
CFLAGS      = -Wall -Wextra -Werror

SRC_DIR     = src
OBJ_DIR     = obj
INC_DIR     = inc
LIBFT_DIR   = libft

SRCS_FILES  = main.c \
              executor/executor.c \
              executor/path_finder.c  \
              signals/signals.c \
			  env/env_utils.c \
			  env/env.c \
			  builtins/env.c \
			  builtins/export.c \
			  builtins/unset.c \
			  builtins/cd.c \
			  builtins/echo.c \
			  builtins/pwd.c \
              utils/free.c \
			  utils/utils.c \
			  lexer/lexer.c \
			  lexer/token.c \
			  expander/expander.c \


SRCS        = $(addprefix $(SRC_DIR)/, $(SRCS_FILES))

OBJS        = $(addprefix $(OBJ_DIR)/, $(SRCS_FILES:.c=.o))

LIBFT       = $(LIBFT_DIR)/libft.a
LIBS        = -L$(LIBFT_DIR) -lft -lreadline
INCLUDES    = -I $(INC_DIR) -I $(LIBFT_DIR)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re