/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_numeric.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 06:59:24 by landriam          #+#    #+#             */
/*   Updated: 2025/12/27 06:14:29 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_error(char *str)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (!str[0])
		return (1);
	if (str[0] == '-' || str[0] == '+')
	{
		if (!str[1])
			return (exit_error(str), 1);
		i++;
	}
	while (str[i])
	{
		if (!(str[i] >= 48 && str[i] <= 57))
			return (exit_error(str), 1);
		i++;
	}
	return (0);
}

static int	check_limit(char *str)
{
	if (!str)
		return (0);
	if (is_numeric(str))
		return (1);
	if (str[0] == '-')
	{
		if (ft_strlen(str + 1) > 19)
			return (exit_error(str), 1);
		if (ft_strcmp("-9223372036854775808", str) < 0)
			return (exit_error(str), 1);
		return (0);
	}
	if (str[0] == '+')
	{
		if (ft_strlen(str + 1) > 19)
			return (exit_error(str), 1);
		if (ft_strcmp("+9223372036854775807", str) < 0)
			return (exit_error(str), 1);
		return (0);
	}
	if (ft_strlen(str) > 19)
		return (exit_error(str), 1);
	if (ft_strcmp("9223372036854775807", str) < 0)
		return (exit_error(str), 1);
	return (0);
}

static int	ft_get_nbr(t_list **var, char *str, int *nbr)
{
	int		i;
	char	*res;

	if (str)
	{
		i = 0;
		if (str[0] == '-' || str[0] == '+')
			i++;
		while (str[i])
		{
			res = ft_string_dup(&str[i++], 1);
			if (!res)
				return (1);
			*nbr = (*nbr) * 10 + ft_atoi(res);
			free(res);
		}
		if (str[0] == '-')
			*nbr = -(*nbr);
	}
	else
		*nbr = get_exit_status(var);
	return (0);
}

int	check_numeric(t_list *arg, t_list **var, int *nbr)
{
	int		len;
	char	*str;

	str = NULL;
	if (arg->next)
		str = arg->next->content;
	if (check_limit(str))
		return (2);
	len = lenght_list(arg);
	if (len > 2)
		return (ft_putstr_fd("minishell: exit: too many arguments\n", 2), 1);
	if (ft_get_nbr(var, str, nbr))
		return (1);
	return (0);
}
