/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_list_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 07:28:59 by landriam          #+#    #+#             */
/*   Updated: 2025/12/30 16:18:07 by landriam         ###   ########.fr       */
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

static t_list	*ft_first_list(char *str, t_list **var)
{
	char	*name;
	t_list	*cur;
	t_list	*tmp;

	cur = *var;
	tmp = cur->next;
	name = get_name(cur->content);
	if (!name)
		return (NULL);
	if (!ft_strcmp(str, name))
	{
		*var = tmp;
		return (free(name), cur);
	}
	free(name);
	return (ft_listnew(NULL, 0));
}

static t_list	*ft_get_list(char *str, t_list **var)
{
	char	*name;
	t_list	*tmp;
	t_list	*cur;
	t_list	*nxt;

	cur = *var;
	tmp = cur->next;
	if (!tmp)
		return (ft_first_list(str, var));
	while (tmp)
	{
		nxt = tmp->next;
		name = get_name(tmp->content);
		if (!name)
			return (NULL);
		if (!ft_strcmp(str, name))
		{
			cur->next = nxt;
			return (free(name), tmp);
		}
		free(name);
		cur = cur->next;
		tmp = cur->next;
	}
	return (ft_listnew(NULL, 0));
}

int	ft_remove_list(char *str, t_list **var)
{
	t_list	*tmp;

	if (!var || !*var)
		return (0);
	tmp = ft_get_list(str, var);
	if (!tmp)
		return (1);
	free(tmp->content);
	free(tmp);
	return (0);
}
