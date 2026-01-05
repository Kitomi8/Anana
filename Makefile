CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline -lhistory

DIR = mandatory
BONUS = bonus

SRCS = $(DIR)/ft_list.c $(DIR)/ft_strdup.c $(DIR)/ft_strlen.c $(DIR)/ft_strjoin.c $(DIR)/ft_strcmp.c $(DIR)/ft_putstr_fd.c $(DIR)/ft_itoa.c\
$(DIR)/ft_atoi.c $(DIR)/ft_strchr.c $(DIR)/ft_split.c $(DIR)/ft_clear_array.c $(DIR)/ft_list_array.c $(DIR)/clear_all.c\
$(DIR)/init_action.c $(DIR)/init_paren_action.c $(DIR)/init_goto.c\
$(DIR)/make_type.c $(DIR)/add_back_type.c $(DIR)/clear_type.c $(DIR)/reduce_to_ast.c $(DIR)/reduce_to_cmd.c\
$(DIR)/push_to_stack.c $(DIR)/pop_to_stack.c\
$(DIR)/parse_input.c $(DIR)/lexer.c $(DIR)/ft_get_word.c $(DIR)/takeoff_quote.c $(DIR)/get_heredoc_fd.c\
$(DIR)/fork_here_doc.c $(DIR)/syntaxe_error.c\
$(DIR)/here_document.c $(DIR)/ft_all_character.c $(DIR)/ft_get_file.c\
$(DIR)/get_variable.c $(DIR)/take_variable.c $(DIR)/expand_variable.c\
\
$(DIR)/var_expansion.c $(DIR)/change_variable.c $(DIR)/lenght_type.c $(DIR)/ft_split_quote.c\
$(DIR)/ft_len_globbing.c $(DIR)/ft_check_globbing.c $(DIR)/ft_get_globbing.c $(DIR)/ft_get_star.c $(DIR)/ft_globbing.c\
$(DIR)/ft_cmp_globbing.c $(DIR)/arg_expansion.c $(DIR)/red_expansion.c $(DIR)/red_apply.c\
$(DIR)/ft_check_builting.c\
$(DIR)/is_directory.c $(DIR)/get_path_cmd.c $(DIR)/exec_builting.c $(DIR)/exec_single_cmd.c\
$(DIR)/middle_cmd.c $(DIR)/exec_pipe_cmd.c $(DIR)/exec_cmd.c $(DIR)/exec_sub_cmd.c $(DIR)/sub_pipe_cmd.c $(DIR)/execution.c\
$(DIR)/dup_fd.c $(DIR)/signal_reading.c $(DIR)/signal_handler.c\
$(DIR)/ft_wait.c\
$(DIR)/assign_variable.c $(DIR)/variable_function.c\
$(DIR)/ft_builting.c $(DIR)/ft_remove_list.c\
$(DIR)/echo.c $(DIR)/env.c\
$(DIR)/check_numeric.c $(DIR)/exit.c $(DIR)/ft_sort_env.c $(DIR)/export.c $(DIR)/export_check.c $(DIR)/export_input.c\
$(DIR)/unset.c $(DIR)/ft_pwd.c $(DIR)/check_env.c $(DIR)/take_path_cd.c $(DIR)/current_dir.c\
$(DIR)/get_env.c $(DIR)/minishell.c

SRCS_BONUS = $(BONUS)/ft_list_bonus.c $(BONUS)/ft_strdup_bonus.c $(BONUS)/ft_strlen_bonus.c $(BONUS)/ft_strjoin_bonus.c $(BONUS)/ft_strcmp_bonus.c $(BONUS)/ft_putstr_fd_bonus.c $(BONUS)/ft_itoa_bonus.c\
$(BONUS)/ft_atoi_bonus.c $(BONUS)/ft_strchr_bonus.c $(BONUS)/ft_split_bonus.c $(BONUS)/ft_clear_array_bonus.c $(BONUS)/ft_list_array_bonus.c $(BONUS)/clear_all_bonus.c\
$(BONUS)/init_action_bonus.c $(BONUS)/init_paren_action_bonus.c $(BONUS)/init_goto_bonus.c\
$(BONUS)/make_type_bonus.c $(BONUS)/add_back_type_bonus.c $(BONUS)/clear_type_bonus.c $(BONUS)/reduce_to_ast_bonus.c $(BONUS)/reduce_to_cmd_bonus.c\
$(BONUS)/push_to_stack_bonus.c $(BONUS)/pop_to_stack_bonus.c\
$(BONUS)/parse_input_bonus.c $(BONUS)/lexer_bonus.c $(BONUS)/ft_get_word_bonus.c $(BONUS)/takeoff_quote_bonus.c $(BONUS)/get_heredoc_fd_bonus.c\
$(BONUS)/fork_here_doc_bonus.c $(BONUS)/syntaxe_error_bonus.c\
$(BONUS)/here_document_bonus.c $(BONUS)/ft_all_character_bonus.c $(BONUS)/ft_get_file_bonus.c\
$(BONUS)/get_variable_bonus.c $(BONUS)/take_variable_bonus.c $(BONUS)/expand_variable_bonus.c\
\
$(BONUS)/var_expansion_bonus.c $(BONUS)/change_variable_bonus.c $(BONUS)/lenght_type_bonus.c $(BONUS)/ft_split_quote_bonus.c\
$(BONUS)/ft_len_globbing_bonus.c $(BONUS)/ft_check_globbing_bonus.c $(BONUS)/ft_get_globbing_bonus.c $(BONUS)/ft_get_star_bonus.c $(BONUS)/ft_globbing_bonus.c\
$(BONUS)/ft_cmp_globbing_bonus.c $(BONUS)/arg_expansion_bonus.c $(BONUS)/red_expansion_bonus.c $(BONUS)/red_apply_bonus.c\
$(BONUS)/ft_check_builting_bonus.c\
$(BONUS)/is_directory_bonus.c $(BONUS)/get_path_cmd_bonus.c $(BONUS)/exec_builting_bonus.c $(BONUS)/exec_single_cmd_bonus.c\
$(BONUS)/middle_cmd_bonus.c $(BONUS)/exec_pipe_cmd_bonus.c $(BONUS)/exec_cmd_bonus.c $(BONUS)/exec_sub_cmd_bonus.c $(BONUS)/sub_pipe_cmd_bonus.c $(BONUS)/execution_bonus.c\
$(BONUS)/dup_fd_bonus.c $(BONUS)/signal_reading_bonus.c $(BONUS)/signal_handler_bonus.c\
$(BONUS)/ft_wait_bonus.c\
$(BONUS)/assign_variable_bonus.c $(BONUS)/variable_function_bonus.c\
$(BONUS)/ft_builting_bonus.c $(BONUS)/ft_remove_list_bonus.c\
$(BONUS)/echo_bonus.c $(BONUS)/env_bonus.c\
$(BONUS)/check_numeric_bonus.c $(BONUS)/exit_bonus.c $(BONUS)/ft_sort_env_bonus.c $(BONUS)/export_bonus.c $(BONUS)/export_check_bonus.c $(BONUS)/export_input_bonus.c\
$(BONUS)/unset_bonus.c $(BONUS)/ft_pwd_bonus.c $(BONUS)/check_env_bonus.c $(BONUS)/take_path_cd_bonus.c $(BONUS)/current_dir_bonus.c\
$(BONUS)/get_env_bonus.c $(BONUS)/minishell_bonus.c

OBJS = $(SRCS:$(DIR)/%.c=$(DIR)/%.o)

OBJS_BONUS = $(SRCS_BONUS:$(BONUS)/%.c=$(BONUS)/%.o)

NAME = minishell

NAME_BONUS = minishell_bonus

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@
$(DIR)/%.o: $(DIR)/%.c
	$(CC) $(CFLAGS) -c $< $(LDFLAGS) -o $@
bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@
$(BONUS)/%.o: $(BONUS)/%.c
	$(CC) $(CFLAGS) -c $< $(LDFLAGS) -o $@
clean:
	rm -f $(OBJS) $(OBJS_BONUS)
fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
re: fclean all

.PHONY: all bonus clean fclean re
