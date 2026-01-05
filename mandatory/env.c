/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtoky-fa <rtoky-fa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 09:14:39 by rtoky-fa          #+#    #+#             */
/*   Updated: 2025/12/26 16:45:38 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_list **var, int fd[2])
{
	t_list	*tmp;
	char	*str;

	str = NULL;
	tmp = *var;
	while (tmp)
	{
		if (ft_string_cmp("_=", tmp->content))
		{
			if (tmp->flag > 1)
			{
				ft_putstr_fd(tmp->content, fd[1]);
				ft_putstr_fd("\n", fd[1]);
			}
		}
		else
			str = tmp->content;
		tmp = tmp->next;
	}
	if (str)
	{
		ft_putstr_fd(str, fd[1]);
		ft_putstr_fd("\n", fd[1]);
	}
}
