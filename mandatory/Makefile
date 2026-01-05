CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline -lhistory
SRCS = ft_list.c ft_strdup.c ft_strlen.c ft_strjoin.c ft_strcmp.c ft_putstr_fd.c ft_itoa.c\
ft_atoi.c ft_strchr.c ft_split.c ft_clear_array.c ft_list_array.c clear_all.c\
init_action.c init_paren_action.c init_goto.c\
make_type.c add_back_type.c clear_type.c reduce_to_ast.c reduce_to_cmd.c\
push_to_stack.c pop_to_stack.c\
parse_input.c lexer.c ft_get_word.c takeoff_quote.c get_heredoc_fd.c\
fork_here_doc.c syntaxe_error.c\
here_document.c ft_all_character.c ft_get_file.c\
get_variable.c take_variable.c expand_variable.c\
\
var_expansion.c change_variable.c lenght_type.c ft_split_quote.c\
ft_len_globbing.c ft_check_globbing.c ft_get_globbing.c ft_get_star.c ft_globbing.c\
ft_cmp_globbing.c arg_expansion.c red_expansion.c red_apply.c\
ft_check_builting.c get_path_cmd.c exec_builting.c exec_single_cmd.c\
middle_cmd.c exec_pipe_cmd.c exec_cmd.c exec_sub_cmd.c sub_pipe_cmd.c execution.c\
dup_fd.c signal_reading.c signal_handler.c\
ft_wait.c\
assign_variable.c variable_function.c\
ft_builting.c ft_remove_list.c\
echo.c env.c\
check_numeric.c exit.c ft_sort_env.c export.c export_check.c export_input.c\
unset.c ft_pwd.c check_env.c take_path_cd.c current_dir.c\
get_env.c minishell.c
OBJS = $(SRCS:.c=.o)
NAME = minishell

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@
$(OBJS):%.o:%.c
	$(CC) $(CFLAGS) -c $<
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all

.PHONY: all clean fclean re
