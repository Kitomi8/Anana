/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lenght_type_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 09:46:42 by landriam          #+#    #+#             */
/*   Updated: 2025/12/30 16:22:39 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	lenght_list(t_list *head)
{
	int		len;
	t_list	*tmp;

	if (!head)
		return (0);
	len = 0;
	tmp = head;
	while (tmp)
	{
		if (tmp->content)
			len++;
		tmp = tmp->next;
	}
	return (len);
}

int	lenght_env(t_list *head, int fg)
{
	int		len;
	t_list	*tmp;

	if (!head)
		return (0);
	len = 0;
	tmp = head;
	while (tmp)
	{
		if (tmp->flag >= fg)
			len++;
		tmp = tmp->next;
	}
	return (len);
}

int	lenght_arg(t_wordlist *head)
{
	int			len;
	t_wordlist	*tmp;

	if (!head)
		return (0);
	len = 0;
	tmp = head;
	while (tmp)
	{
		if (tmp->word)
			len++;
		tmp = tmp->next;
	}
	return (len);
}

int	lenght_cmd(t_command *head)
{
	int			len;
	t_command	*tmp;

	if (!head)
		return (0);
	len = 0;
	tmp = head;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}
