/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 22:24:05 by landriam          #+#    #+#             */
/*   Updated: 2025/12/30 16:07:53 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static char	*get_name(char *str)
{
	int		i;
	char	*res;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
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

char	*check_env(char *str, t_list *var)
{
	char	*name;
	char	*res;
	t_list	*tmp;

	tmp = var;
	while (tmp)
	{
		if (tmp->flag == 2)
		{
			name = get_name(tmp->content);
			if (!name)
				return (NULL);
			if (!ft_strcmp(name, str))
			{
				res = value_variable(tmp->content);
				if (!res)
					return (free(name), NULL);
				return (free(name), res);
			}
			free(name);
		}
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}
