/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtoky-fa <rtoky-fa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:04:06 by landriam          #+#    #+#             */
/*   Updated: 2026/01/05 13:53:24 by rtoky-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_list *arg, int fd[2])
{
	int		option;
	t_list	*tmp;

	option = 0;
	tmp = arg->next;
	if (tmp)
	{
		if (!ft_strcmp("-n", tmp->content))
		{
			option = 1;
			tmp = tmp->next;
		}
	}
	while (tmp)
	{
		ft_putstr_fd(tmp->content, fd[1]);
		if (tmp->next)
			ft_putstr_fd(" ", fd[1]);
		tmp = tmp->next;
	}
	if (!option)
		ft_putstr_fd("\n", fd[1]);
}
