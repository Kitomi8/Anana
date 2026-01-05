/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 07:04:06 by landriam          #+#    #+#             */
/*   Updated: 2026/01/05 16:01:55 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_option(char *str)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	if (str[i] == '-')
	{
		i++;
		while (str[i])
		{
			if (str[i] != 'n')
			{
				check = 1;
				break ;
			}
			i++;
		}
		if (!check)
			return (0);
	}
	return (1);
}

void	echo(t_list *arg, int fd[2])
{
	int		option;
	t_list	*tmp;

	option = 0;
	tmp = arg->next;
	while (tmp)
	{
		if (!check_option(tmp->content))
		{
			option = 1;
			tmp = tmp->next;
		}
		else
			break ;
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
