/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 09:08:31 by landriam          #+#    #+#             */
/*   Updated: 2025/12/26 17:12:06 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_name(char *str, int *check)
{
	int		i;
	char	*res;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			*check = 1;
			break ;
		}
		i++;
	}
	res = ft_string_dup(str, i);
	if (!res)
		return (NULL);
	return (res);
}

static char	*value_variable(char *var)
{
	int		i;
	int		len;
	char	*res;

	i = 0;
	len = 0;
	while (var[i])
	{
		if (var[i] == '=')
		{
			len++;
			break ;
		}
		i++;
	}
	if (!len)
		res = ft_strdup("");
	else
		res = ft_strdup(var + i + 1);
	if (!res)
		return (NULL);
	return (res);
}

static int	env_print(char *str, int fds[2])
{
	char	*des;

	des = value_variable(str);
	if (!des)
		return (1);
	ft_putstr_fd("=\"", fds[1]);
	ft_putstr_fd(des, fds[1]);
	ft_putstr_fd("\"", fds[1]);
	free(des);
	return (0);
}

static int	ft_print_env(char **arr, int check, int fds[2])
{
	int		i;
	char	*str;

	i = 0;
	while (arr[i])
	{
		check = 0;
		if (ft_string_cmp("_=", arr[i]))
		{
			str = get_name(arr[i], &check);
			if (!str)
				return (1);
			ft_putstr_fd("export ", fds[1]);
			ft_putstr_fd(str, fds[1]);
			if (check)
			{
				if (env_print(arr[i], fds))
					return (free(str), 1);
			}
			ft_putstr_fd("\n", fds[1]);
			free(str);
		}
		i++;
	}
	return (0);
}

int	ft_export(t_list *arg, t_list **var, int fds[2])
{
	int		len;
	int		check;
	char	**arr;
	t_list	*env;

	env = *var;
	check = 0;
	len = lenght_list(arg);
	if (len == 1)
	{
		arr = ft_array_env(env, 1);
		if (!arr)
			return (1);
		ft_sort_env(arr);
		ft_print_env(arr, check, fds);
		ft_clear_array(arr);
	}
	else
	{
		if (export_check(arg, var))
			return (1);
	}
	return (0);
}
