/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 07:50:23 by landriam          #+#    #+#             */
/*   Updated: 2025/12/29 18:04:03 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_name(char *str)
{
	int		i;
	char	*res;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	res = ft_string_dup(str, i);
	if (!res)
		return (NULL);
	return (res);
}

static char	*value_variable(char *var)
{
	int		i;
	char	*res;

	i = 0;
	while (var[i] != '=')
		i++;
	res = ft_strdup(var + (i + 1));
	if (!res)
		return (NULL);
	return (res);
}

char	*get_variable(char *str, t_list *lst)
{
	char	*name;
	char	*res;
	t_list	*tmp;

	if (!str)
		return (NULL);
	tmp = lst;
	res = NULL;
	while (tmp)
	{
		name = get_name(tmp->content);
		if (!name)
			return (NULL);
		if (!ft_strcmp(str + 1, name))
		{
			res = value_variable(tmp->content);
			if (!res)
				return (free(name), NULL);
			return (free(name), res);
		}
		free(name);
		tmp = tmp->next;
	}
	res = ft_strdup("");
	return (res);
}
