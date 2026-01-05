/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_type_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:41:33 by landriam          #+#    #+#             */
/*   Updated: 2025/12/30 16:08:44 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	clear_wordlist(t_wordlist **head)
{
	t_wordlist	*tmp;
	t_wordlist	*cur;

	tmp = *head;
	if (!head || !tmp)
		return ;
	while (tmp)
	{
		cur = tmp->next;
		free(tmp->word);
		free(tmp);
		tmp = cur;
	}
	*head = NULL;
}

void	clear_redirect(t_redirect **head)
{
	t_redirect	*tmp;
	t_redirect	*cur;

	tmp = *head;
	if (!head || !tmp)
		return ;
	while (tmp)
	{
		cur = tmp->next;
		free(tmp->body);
		free(tmp);
		tmp = cur;
	}
	*head = NULL;
}

void	clear_command(t_command **head)
{
	t_command	*tmp;
	t_command	*cur;
	t_node		*node;

	if (!head || !*head)
		return ;
	tmp = *head;
	while (tmp)
	{
		node = (t_node *)tmp->node;
		cur = tmp->next;
		clear_wordlist(&tmp->arg);
		clear_redirect(&tmp->redirect);
		clear_node(&node);
		free(tmp);
		tmp = cur;
	}
	*head = NULL;
}

void	clear_node(t_node **node)
{
	t_node	*tmp;

	if (!node || !*node)
		return ;
	tmp = *node;
	clear_command(&tmp->command);
	clear_node(&tmp->left);
	clear_node(&tmp->right);
	free(tmp);
	*node = NULL;
}

void	clear_stack(t_stacktype *stack, int *top)
{
	t_stacktype	*head;
	t_command	*cmd;
	t_node		*node;

	while (*top > 0)
	{
		head = stack + *top;
		if (head->type == PIPELINE || head->type == SEQUENCE)
		{
			node = pop_node(stack, top);
			clear_node(&node);
		}
		else if (head->type == COMMAND)
		{
			cmd = pop_command(stack, top);
			clear_command(&cmd);
		}
		else
		{
			if (head->type == WORD)
				free(head->word);
			pop_terminal(stack, top);
		}
	}
}
