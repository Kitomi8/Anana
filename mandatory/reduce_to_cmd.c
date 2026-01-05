/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce_to_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:42:28 by landriam          #+#    #+#             */
/*   Updated: 2025/11/01 21:59:10 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reduce_word(t_stacktype *stack, int *top)
{
	int			act;
	char		*str;
	t_command	*command;

	str = pop_terminal(stack, top);
	command = make_command(make_wordlist(str), NULL, NULL);
	act = init_goto(stack[*top].state, COMMAND_SIMPLE);
	push_cmd(stack, top, act, command);
}

void	reduce_red_cmd(t_stacktype *stack, int *top)
{
	int			act;
	t_redirect	*redirect;
	t_command	*command;

	redirect = pop_redirect(stack, top);
	command = make_command(NULL, redirect, NULL);
	act = init_goto(stack[*top].state, COMMAND_SIMPLE);
	push_cmd(stack, top, act, command);
}

void	reduce_redirect(t_stacktype *stack, int *top, t_here_doc **doc)
{
	int			act;
	char		*str;
	t_nodetype	type;
	t_redirect	*redirect;

	str = pop_terminal(stack, top);
	type = stack[*top].type;
	pop_terminal(stack, top);
	if (type == DLESS)
	{
		addback_here_doc(doc, make_here_doc(str));
		redirect = make_redirect(type, ft_strdup(str));
	}
	else
		redirect = make_redirect(type, str);
	act = init_goto(stack[*top].state, REDIRECT);
	push_red(stack, top, act, redirect);
}

void	reduce_cmd_word(t_stacktype *stack, int *top)
{
	int			act;
	char		*str;
	t_command	*command;

	str = pop_terminal(stack, top);
	command = pop_command(stack, top);
	add_back_wordlist(&command->arg, make_wordlist(str));
	act = init_goto(stack[*top].state, COMMAND_SIMPLE);
	push_cmd(stack, top, act, command);
}

void	reduce_cmd_red(t_stacktype *stack, int *top)
{
	int			act;
	t_nodetype	type;
	t_redirect	*redirect;
	t_command	*command;

	redirect = pop_redirect(stack, top);
	command = pop_command(stack, top);
	add_back_redirect(&command->redirect, redirect);
	type = command->type;
	act = init_goto(stack[*top].state, type);
	push_cmd(stack, top, act, command);
}
