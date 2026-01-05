/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 05:09:58 by landriam          #+#    #+#             */
/*   Updated: 2025/12/30 16:24:39 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_BONUS_H
# define PARSE_BONUS_H

typedef enum e_nodetype
{
	WORD,
	LESS,
	GREAT,
	DLESS,
	DGREAT,
	PIPE,
	OPEN_PAREN,
	CLOSE_PAREN,
	AND,
	OR,
	END,
	REDIRECT,
	COMMAND,
	COMMAND_SIMPLE,
	COMMAND_COMPOUND,
	PIPELINE,
	SEQUENCE,
	SEQUENCE_AND,
	SEQUENCE_OR,
	START,
	ERROR
}	t_nodetype;

typedef struct s_token
{
	t_nodetype	type;
	char		*value;
}	t_token;

typedef struct s_wordlist
{
	char				*word;
	struct s_wordlist	*next;
}	t_wordlist;

typedef struct s_redirect
{
	t_nodetype			type;
	int					fd;
	char				*body;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_here_doc
{
	char				*delimiter;
	char				*source;
	int					flags;
	int					fd;
	struct s_here_doc	*next;
}	t_here_doc;

typedef struct s_command
{
	t_nodetype			type;
	t_wordlist			*arg;
	t_redirect			*redirect;
	void				*node;
	struct s_command	*next;
}	t_command;

typedef struct s_node
{
	t_nodetype		type;
	t_command		*command;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

typedef struct s_stacktype
{
	int			state;
	t_nodetype	type;
	char		*word;
	t_redirect	*redirect;
	t_command	*command;
	t_node		*node;
}	t_stacktype;

int			three_first_state(int state, t_nodetype terminal);
int			action_state(int state, t_nodetype terminal);
int			two_last_state(int state, t_nodetype terminal);
int			init_second_action(int state, t_nodetype term);
int			init_action(int state, t_nodetype terminal);
int			init_goto(int state, t_nodetype non_term);

void		push_ter(t_stacktype *stack, int *top, int state, t_token *token);
void		push_red(t_stacktype *stack, int *top, int state, t_redirect *red);
void		push_cmd(t_stacktype *stack, int *top, int state, t_command *cmd);
void		push_npipe(t_stacktype *stack, int *top, int state, t_node *node);
void		push_nseq(t_stacktype *stack, int *top, int state, t_node *node);

char		*pop_terminal(t_stacktype *stack, int *top);
t_redirect	*pop_redirect(t_stacktype *stack, int *top);
t_command	*pop_command(t_stacktype *stack, int *top);
t_node		*pop_node(t_stacktype *stack, int *top);

t_wordlist	*make_wordlist(char *word);
t_redirect	*make_redirect(t_nodetype type, char *body);
t_command	*make_command(t_wordlist *wlst, t_redirect *red, t_node *node);
t_node		*make_node_pipe(t_command *command);
t_node		*make_node_seq(t_nodetype type, t_node *left, t_node *right);

void		add_back_wordlist(t_wordlist **head, t_wordlist *news);
void		add_back_redirect(t_redirect **head, t_redirect *news);
void		add_back_command(t_command **head, t_command *news);

void		clear_wordlist(t_wordlist **head);
void		clear_redirect(t_redirect **head);
void		clear_command(t_command **head);
void		clear_node(t_node **node);
void		clear_stack(t_stacktype *stack, int *top);

void		reduce_word(t_stacktype *stack, int *top);
void		reduce_red_cmd(t_stacktype *stack, int *top);
void		reduce_redirect(t_stacktype *stack, int *top, t_here_doc **doc);
void		reduce_cmd_word(t_stacktype *stack, int *top);
void		reduce_cmd_red(t_stacktype *stack, int *top);

void		reduce_cmd_pipe(t_stacktype *stack, int *top);
void		reduce_pipe(t_stacktype *stack, int *top);
void		reduce_pipe_seq(t_stacktype *stack, int *top);
void		reduce_seq(t_stacktype *stack, int *top);
void		reduce_paren(t_stacktype *stack, int *top);

t_here_doc	*make_here_doc(char *delimiter);
void		addback_here_doc(t_here_doc **head, t_here_doc *news);
void		rmvtop_here_doc(t_here_doc **head);
void		clear_here_doc(t_here_doc **head);
char		*takeoff_quote(char *str);

void		syntaxe_error(t_token *token);
int			ft_isnormal_char(char c);
int			ft_isall_char(char c);
int			ft_ismeta_char(char c);
int			ft_is_char(char *str);
void		ft_isquote(char c, int *squote, int *dquote);

#endif
