/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_back_type_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:41:16 by landriam          #+#    #+#             */
/*   Updated: 2025/12/30 16:06:44 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	add_back_wordlist(t_wordlist **head, t_wordlist *news)
{
	t_wordlist	*tmp;

	if (!head || !news)
		return ;
	tmp = *head;
	if (!tmp)
	{
		*head = news;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = news;
}

void	add_back_redirect(t_redirect **head, t_redirect *news)
{
	t_redirect	*tmp;

	if (!head || !news)
		return ;
	tmp = *head;
	if (!tmp)
	{
		*head = news;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = news;
}

void	add_back_command(t_command **head, t_command *news)
{
	t_command	*tmp;

	if (!head || !news)
		return ;
	tmp = *head;
	if (!tmp)
	{
		*head = news;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = news;
}
