/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_to_stack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:22:59 by landriam          #+#    #+#             */
/*   Updated: 2025/11/01 21:00:09 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	push_ter(t_stacktype *stack, int *top, int state, t_token *token)
{
	t_stacktype	*head;

	*top = *top + 1;
	head = stack + (*top);
	head->state = state;
	head->type = token->type;
	head->word = token->value;
	head->redirect = NULL;
	head->command = NULL;
	head->node = NULL;
}

void	push_red(t_stacktype *stack, int *top, int state, t_redirect *red)
{
	t_stacktype	*head;

	*top = *top + 1;
	head = stack + (*top);
	head->state = state;
	head->type = REDIRECT;
	head->word = NULL;
	head->redirect = red;
	head->command = NULL;
	head->node = NULL;
}

void	push_cmd(t_stacktype *stack, int *top, int state, t_command *cmd)
{
	t_stacktype	*head;

	*top = *top + 1;
	head = stack + (*top);
	head->state = state;
	head->type = COMMAND;
	head->word = NULL;
	head->redirect = NULL;
	head->command = cmd;
	head->node = NULL;
}

void	push_npipe(t_stacktype *stack, int *top, int state, t_node *node)
{
	t_stacktype	*head;

	*top = *top + 1;
	head = stack + (*top);
	head->state = state;
	head->type = PIPELINE;
	head->word = NULL;
	head->redirect = NULL;
	head->command = NULL;
	head->node = node;
}

void	push_nseq(t_stacktype *stack, int *top, int state, t_node *node)
{
	t_stacktype	*head;

	*top = *top + 1;
	head = stack + (*top);
	head->state = state;
	head->type = SEQUENCE;
	head->word = NULL;
	head->redirect = NULL;
	head->command = NULL;
	head->node = node;
}
