/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reduce_to_ast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:42:13 by landriam          #+#    #+#             */
/*   Updated: 2025/10/25 16:36:38 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reduce_cmd_pipe(t_stacktype *stack, int *top)
{
	int			act;
	t_command	*command;
	t_node		*node;

	command = pop_command(stack, top);
	node = make_node_pipe(command);
	act = init_goto(stack[*top].state, PIPELINE);
	push_npipe(stack, top, act, node);
}

void	reduce_pipe(t_stacktype *stack, int *top)
{
	int			act;
	t_command	*command;
	t_node		*node;

	command = pop_command(stack, top);
	pop_terminal(stack, top);
	node = pop_node(stack, top);
	add_back_command(&node->command, command);
	act = init_goto(stack[*top].state, PIPELINE);
	push_npipe(stack, top, act, node);
}

void	reduce_pipe_seq(t_stacktype *stack, int *top)
{
	int		act;
	t_node	*node;

	node = pop_node(stack, top);
	act = init_goto(stack[*top].state, SEQUENCE);
	push_nseq(stack, top, act, node);
}

void	reduce_seq(t_stacktype *stack, int *top)
{
	int			act;
	t_nodetype	type;
	t_node		*left;
	t_node		*right;
	t_node		*node;

	right = pop_node(stack, top);
	type = stack[*top].type;
	pop_terminal(stack, top);
	left = pop_node(stack, top);
	node = make_node_seq(type, left, right);
	act = init_goto(stack[*top].state, type);
	push_nseq(stack, top, act, node);
}

void	reduce_paren(t_stacktype *stack, int *top)
{
	int			act;
	t_node		*node;
	t_command	*command;

	pop_terminal(stack, top);
	node = pop_node(stack, top);
	pop_terminal(stack, top);
	command = make_command(NULL, NULL, node);
	act = init_goto(stack[*top].state, COMMAND_COMPOUND);
	push_cmd(stack, top, act, command);
}
