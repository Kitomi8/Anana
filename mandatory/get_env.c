/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:00:24 by landriam          #+#    #+#             */
/*   Updated: 2025/12/24 07:31:22 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*get_env(char **env)
{
	int		i;
	char	*str;
	t_list	*var;

	if (!env || !env[0])
		return (NULL);
	i = 0;
	str = NULL;
	var = NULL;
	while (env[i + 1])
	{
		str = ft_strdup(env[i]);
		if (!str)
		{
			write(2, "Memory allocation failed!\n", 26);
			return (ft_listclear(&var), NULL);
		}
		ft_listadd_back(&var, ft_listnew(str, 2));
		i++;
	}
	return (var);
}

static int	pwd_env(t_list **var)
{
	int		check;
	char	*str;
	char	*str1;

	str1 = get_pwd();
	if (!str1)
		return (1);
	check = assign_variable(*var, "PWD", str1);
	if (!check)
	{
		str = ft_strjoin("PWD=", str1);
		if (!str)
			return (free(str1), 1);
		ft_listadd_back(var, ft_listnew(str, 2));
	}
	free(str1);
	if (check == -1)
		return (1);
	return (0);
}

int	input_variable(t_list **var)
{
	char	*str1;

	str1 = ft_strdup("?=0");
	if (!str1)
		return (ft_listclear(var), 1);
	ft_listadd_back(var, ft_listnew(str1, 0));
	str1 = ft_strdup("_=./minishell");
	if (!str1)
		return (ft_listclear(var), 1);
	ft_listadd_back(var, ft_listnew(str1, 1));
	if (pwd_env(var))
		return (ft_listclear(var), 1);
	return (0);
}
