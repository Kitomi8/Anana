/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:02:14 by landriam          #+#    #+#             */
/*   Updated: 2025/10/28 18:24:46 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	do_expansion(char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			return (0);
		i++;
	}
	return (1);
}

t_here_doc	*make_here_doc(char *delimiter)
{
	t_here_doc	*here;

	here = (t_here_doc *)malloc(sizeof(t_here_doc));
	if (!here)
		return (NULL);
	here->delimiter = delimiter;
	here->source = NULL;
	here->flags = do_expansion(delimiter);
	here->fd = -1;
	here->next = NULL;
	return (here);
}

void	addback_here_doc(t_here_doc **head, t_here_doc *news)
{
	t_here_doc	*tmp;

	if (!head || !news)
		return ;
	if (!*head)
	{
		*head = news;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = news;
}

void	rmvtop_here_doc(t_here_doc **head)
{
	t_here_doc	*tmp;
	t_here_doc	*cur;

	if (!head || !*head)
		return ;
	tmp = *head;
	cur = tmp->next;
	free(tmp->delimiter);
	free(tmp->source);
	free(tmp);
	tmp = NULL;
	*head = cur;
}

void	clear_here_doc(t_here_doc **head)
{
	t_here_doc	*tmp;
	t_here_doc	*cur;

	if (!head || !*head)
		return ;
	tmp = *head;
	while (tmp)
	{
		cur = tmp->next;
		free(tmp->delimiter);
		free(tmp->source);
		free(tmp);
		tmp = NULL;
		tmp = cur;
	}
	*head = NULL;
}
