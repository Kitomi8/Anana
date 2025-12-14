/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtoky-fa <rtoky-fa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 09:14:43 by rtoky-fa          #+#    #+#             */
/*   Updated: 2025/12/12 10:52:17 by rtoky-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_n_flag(char *arg)
{
	int	i;

	i = 1;
	if (!arg && arg[0] != '-')
		return (0);
	if (!arg[1])
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **args)
{
	int	i;
	int	no_newline;

	i = 0;
	no_newline = 0;
	while (args[i])
	{
		if (args[i] && is_n_flag(args[i]))
			no_newline = 1;
		i++;
	}
	i = 1;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (no_newline == 0)
		ft_putchar_fd('\n', 1);
	return (0);
}
