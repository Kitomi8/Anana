/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:43:25 by landriam          #+#    #+#             */
/*   Updated: 2026/01/05 15:56:49 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	reduce(int act, t_stacktype *stack, int *top, t_here_doc **doc)
{
	if (act == -5)
		reduce_cmd_pipe(stack, top);
	if (act == -6)
		reduce_pipe(stack, top);
	if (act == -2)
		reduce_pipe_seq(stack, top);
	if (act == -3 || act == -4)
		reduce_seq(stack, top);
	if (act == -7)
		reduce_word(stack, top);
	if (act == -8)
		reduce_red_cmd(stack, top);
	if (act == -9)
		reduce_cmd_word(stack, top);
	if (act == -10)
		reduce_cmd_red(stack, top);
	if (act == -12)
		reduce_redirect(stack, top, doc);
	if (act == -11)
		reduce_paren(stack, top);
}

static void	close_fd(t_here_doc **doc)
{
	t_here_doc	*tmp;

	if (!doc || !*doc)
		return ;
	tmp = *doc;
	while (tmp)
	{
		if (tmp->source)
		{
			if (tmp->fd > 2)
				close(tmp->fd);
			unlink(tmp->source);
		}
		tmp = tmp->next;
	}
}

t_node	*core(char **copy, t_stacktype *stack, int *top, t_here_doc **doc)
{
	int		act;
	int		check;
	t_token	lookahead;

	check = 0;
	lookahead = lexer(copy);
	while (lookahead.type != ERROR)
	{
		act = init_action(stack[*top].state, lookahead.type);
		if (act == 999)
			return (pop_node(stack, top));
		else if (act > 0 && act < 999)
		{
			push_ter(stack, top, act, &lookahead);
			lookahead = lexer(copy);
		}
		else if (act < 0)
			reduce(act, stack, top, doc);
		else
			return (syntaxe_error(&lookahead), NULL);
		if (act == -12 && stack[*top].redirect->type == DLESS)
			stack[*top].redirect->fd = check++;
	}
	return (NULL);
}

t_node	*parse_input(char *input, t_here_doc **doc, t_list *var)
{
	int			top;
	int			status;
	char		*copy;
	t_node		*node;
	t_stacktype	stack[10];

	top = 0;
	copy = input;
	stack[0].state = 0;
	node = core(&copy, stack, &top, doc);
	if (!node)
	{
		exit_status(var, 2);
		clear_stack(stack, &top);
	}
	status = parse_here_doc(doc, var);
	if (status)
	{
		exit_status(var, status);
		return (clear_node(&node), close_fd(doc), NULL);
	}
	return (node);
}
