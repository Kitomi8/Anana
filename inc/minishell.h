/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtoky-fa <rtoky-fa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 14:24:46 by rtoky-fa          #+#    #+#             */
/*   Updated: 2025/12/16 14:25:22 by rtoky-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_env
{
	char *key;   // Ex: "HOME"
	char *value; // Ex: "/home/rtoky-fa"
	struct s_env	*next;
}					t_env;

typedef enum e_token_type
{
	WORD,
	PIPE,
}					t_token_type;

typedef enum e_state
{
	DEFAULT,
	LINKED,
	D_QUOTE,
}					t_state;

typedef struct s_token
{
	char			*content;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

extern int			g_signal;
t_env				*get_env_list(char **envp);
t_env				*ft_envnew(char *key, char *value);
void				ft_envadd_back(t_env **lst, t_env *new);
int					ft_unset(t_env **env, char **args);
int					ft_pwd(void);
t_token				*ft_token_new(char *content, t_token_type type);
void				ft_token_add_back(t_token **lst, t_token *new);
t_token				*ft_lexer(char *line);
t_state				ft_set_state(char quote, t_state state);
int					is_separator(char c);
int					ft_cd(char **args, t_env **env);
void				update_env_var(t_env **env, char *key, char *value);
t_env				*get_env_node(t_env *env, char *key);
char				*get_env_value(t_env *env, char *key);
int					ft_env(t_env *env);
int					ft_export(t_env **env, char **args);
void				init_signals(void);
void				free_tab(char **tab);
void				execute_simple_cmd(char **args, char **envp);
char				*find_executable(char *cmd, char **envp);
int					ft_strcmp(char *s1, char *s2);
char				*remove_quotes(char *str);
void				ft_expand(t_token *token_list, t_env *env);
int					ft_echo(char **args);
int					count_token_list(t_token *tokens);
char				**token_to_tab(t_token *tokens);
void				free_tokens(t_token *tokens);

#endif