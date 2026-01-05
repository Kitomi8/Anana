/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:00:47 by landriam          #+#    #+#             */
/*   Updated: 2025/12/30 09:45:10 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include <stdlib.h>
# include <unistd.h>

# include <fcntl.h>

# include <string.h>
# include <errno.h>

# include <dirent.h>

# include <sys/types.h>
# include <sys/wait.h>

# include <sys/stat.h>

# include "parse.h"

extern volatile sig_atomic_t	g_sig;

typedef struct s_data
{
	int		error;
	char	*word;
}	t_data;

typedef struct s_list
{
	char			*content;
	int				flag;
	struct s_list	*next;
}	t_list;

typedef struct s_store
{
	t_list		*var;
	t_here_doc	*doc;
	t_node		*node;
	t_command	*cmd;
}	t_store;

t_list	*ft_listnew(char *str, int fg);
void	ft_listadd_back(t_list **lst, t_list *new);
void	ft_listclear(t_list **lst);
int		ft_linkedlen_content(t_list *head);
char	*ft_linkedlst_string(t_list *lst);
int		ft_remove_list(char *str, t_list **var);

char	**ft_array_list(t_list *head);
char	**ft_array_env(t_list *head, int fg);

int		ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_string_cmp(const char *s1, const char *s2);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strlen(const char *str);
char	*ft_strdup(const char *s);
char	*ft_string_dup(const char *s, int lenght);
char	*ft_itoa(int n);
int		ft_atoi(const char *nptr);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
void	ft_clear_array(char **arr);
void	clear_all(t_store *store);

t_node	*parse_input(char *input, t_here_doc **doc, t_list *var);
t_token	lexer(char **src);
char	*ft_get_word(char *str, int *lenght);

char	*get_variable(char *str, t_list *lst);
char	*take_variable(char **str);
char	*expand_variable(char *str, t_list *lst);
char	*ft_get_file(int i);
char	*get_heredoc_fd(char *str, t_list *var, int flag);
int		parse_here_doc(t_here_doc **doc, t_list *var);

int		lenght_list(t_list *head);
int		lenght_env(t_list *head, int fg);
int		lenght_arg(t_wordlist *head);
int		lenght_cmd(t_command *head);

char	*change_variable(char **str, int *squote, int *dquote);
char	*var_expansion(char *str, t_list *lst);

t_list	*ft_split_quote(char *str);
int		ft_len_globbing(t_list *lst, int i, int *flag);
t_list	*ft_check_globbing(t_list **lst, int *i);
t_list	*ft_get_globbing(t_list *lst);
char	*ft_get_star(t_list *lst, int i);
t_list	*ft_globbing(t_list *top);

int		ft_all_globbing(t_list **head);
int		ft_cmp_middle(char *entry, char *str, int *len);
int		ft_cmp_last(char *entry, char *str, int *len);
int		ft_cmp_first(char *entry, char *str, int *len);
int		ft_cmp_entry(int flag, char *entry, char *str, int *len);

t_list	*arg_expansion(t_wordlist *head, t_list *lst);
t_list	*red_expansion(char *word, t_list *var);
int		red_apply(t_redirect *head, t_here_doc **doc, t_list *var);

int		ft_check_builting(char *str);
int		is_directory(char *str, char *way);
t_data	get_path(char *str, t_list *var);
int		exec_builting(t_store *store, t_store *all);
int		exec_single_cmd(t_command *cmd, t_here_doc **doc, t_list *var);
void	mid_cmd(t_store *store, t_store *all);
int		exec_pipe_cmd(t_store *store, t_store *all);
int		exec_cmd(t_store *store, t_store *all);
int		exec_sub_cmd(t_store *store, t_store *all);
pid_t	sub_cmd_pipe(t_store *store, t_store *all, int *fd);
int		execution(t_store *store, t_store *all);

void	ft_close(int *pipefd);
void	dup_fd(int *pipefd, int fd);
int		ft_wait(pid_t *pids, int len);
int		signal_reading(void);
int		ignore_signal(void);
int		default_signal(void);
int		signal_heredoc(void);
int		fork_signal(void);

int		assign_variable(t_list *var, char *name, char *key);
void	exit_status(t_list *var, int nbr);
int		last_argument(t_list *var, t_list *arg);
int		ft_builting(t_list **arg, t_store *store, int fds[2], t_store *all);
void	echo(t_list *arg, int fd[2]);
void	env(t_list **var, int fd[2]);
int		get_exit_status(t_list **var);
int		check_numeric(t_list *arg, t_list **var, int *nbr);
int		ft_exit(t_list **arg, t_store *store, t_store *all, int fds[2]);
void	ft_sort_env(char **arr);
int		ft_export(t_list *arg, t_list **var, int fds[2]);
int		export_check(t_list *arg, t_list **var);
int		export_input(char *str, t_list **var);
int		ft_unset(t_list *arg, t_list **var);
char	*get_pwd(void);
int		ft_pwd(int fds[2]);
char	*check_env(char *str, t_list *var);
char	*take_path(char *res, char *pwd, char *tmp);
int		current_dir(t_list *arg, t_list **var);

int		input_variable(t_list **var);
t_list	*get_env(char **env);
#endif
