/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_star_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:03:10 by landriam          #+#    #+#             */
/*   Updated: 2025/12/30 16:15:48 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static char	*ft_check_quote(int flag, char *content, int *check)
{
	int	i;

	i = 0;
	*check = 0;
	if (flag != 0)
		return (takeoff_quote(content));
	else
	{
		while (content[i])
		{
			if (content[i] == 32)
			{
				(*check)++;
				break ;
			}
			i++;
		}
		return (ft_string_dup(content, i));
	}
}

static char	*ft_core_star(t_list *lst, char *str)
{
	int		check;
	char	*src;
	char	*res;
	char	*copy;
	t_list	*tmp;

	check = 0;
	tmp = lst;
	copy = ft_strdup(str);
	while (tmp)
	{
		src = ft_check_quote(tmp->flag, tmp->content, &check);
		if (!src)
			return (free(copy), NULL);
		res = ft_strjoin(copy, src);
		free(copy);
		free(src);
		copy = res;
		if (check)
			break ;
		tmp = tmp->next;
	}
	return (copy);
}

char	*ft_get_star(t_list *lst, int i)
{
	int		check;
	char	*str;
	char	*res;
	t_list	*tmp;

	while (lst->content[i] == 32)
		i++;
	check = 0;
	str = ft_check_quote(lst->flag, lst->content + i, &check);
	if (!str)
		return (NULL);
	if (check)
		return (str);
	tmp = lst->next;
	res = ft_core_star(tmp, str);
	if (!res)
		return (free(str), NULL);
	free(str);
	return (res);
}
