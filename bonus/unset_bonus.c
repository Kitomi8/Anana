/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 07:17:48 by landriam          #+#    #+#             */
/*   Updated: 2025/12/30 16:28:08 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	ft_unset(t_list *arg, t_list **var)
{
	t_list	*tmp;

	if (!arg)
		return (0);
	tmp = arg->next;
	if (!tmp)
		return (0);
	while (tmp)
	{
		if (ft_remove_list(tmp->content, var))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
