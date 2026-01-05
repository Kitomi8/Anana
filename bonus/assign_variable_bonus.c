/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_variable_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:27:46 by landriam          #+#    #+#             */
/*   Updated: 2025/12/30 16:07:21 by landriam         ###   ########.fr       */
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

int	get_exit_status(t_list **var)
{
	int		nbr;
	char	*name;
	char	*value;
	t_list	*tmp;

	tmp = *var;
	while (tmp)
	{
		name = get_name(tmp->content);
		if (!name)
			return (1);
		if (!ft_strcmp("?", name))
		{
			free(name);
			break ;
		}
		free(name);
		tmp = tmp->next;
	}
	value = value_variable(tmp->content);
	if (!value)
		return (1);
	nbr = ft_atoi(value);
	return (free(value), nbr);
}

int	assign_variable(t_list *var, char *name, char *key)
{
	char	*str;
	char	*res;
	t_list	*tmp;

	tmp = var;
	while (tmp)
	{
		if (!ft_string_cmp(name, tmp->content))
		{
			str = ft_strjoin(name, "=");
			if (!str)
				return (-1);
			res = ft_strjoin(str, key);
			if (!res)
				return (free(str), -1);
			free(str);
			free(tmp->content);
			tmp->content = res;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
