/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_type_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:40:46 by landriam          #+#    #+#             */
/*   Updated: 2025/12/30 16:23:04 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

t_wordlist	*make_wordlist(char *word)
{
	t_wordlist	*wordlist;

	wordlist = (t_wordlist *)malloc(sizeof(t_wordlist));
	if (!wordlist)
		return (NULL);
	wordlist->word = word;
	wordlist->next = NULL;
	return (wordlist);
}

t_redirect	*make_redirect(t_nodetype type, char *body)
{
	t_redirect	*redirect;

	redirect = (t_redirect *)malloc(sizeof(t_redirect));
	if (!redirect)
		return (NULL);
	redirect->type = type;
	redirect->fd = -1;
	redirect->body = body;
	redirect->next = NULL;
	return (redirect);
}

t_command	*make_command(t_wordlist *wlst, t_redirect *red, t_node *node)
{
	t_command	*command;

	command = (t_command *)malloc(sizeof(t_command));
	if (!command)
		return (NULL);
	if (!node)
		command->type = COMMAND_SIMPLE;
	else
		command->type = COMMAND_COMPOUND;
	command->arg = wlst;
	command->redirect = red;
	command->node = node;
	command->next = NULL;
	return (command);
}

t_node	*make_node_pipe(t_command *command)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = PIPELINE;
	node->command = command;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_node	*make_node_seq(t_nodetype type, t_node *left, t_node *right)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->command = NULL;
	node->left = left;
	node->right = right;
	return (node);
}
