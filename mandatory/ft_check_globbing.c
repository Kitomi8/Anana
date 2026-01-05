/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_globbing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:01:48 by landriam          #+#    #+#             */
/*   Updated: 2025/12/27 17:10:51 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_str_globbing(t_list **lst, int *i, int len)
{
	int		j;
	char	*res;
	t_list	*tmp;

	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	tmp = *lst;
	j = 0;
	while (tmp)
	{
		if (!tmp->flag)
		{
			while (tmp->content[*i] == 42)
				(*i)++;
		}
		while (tmp->content[*i] && j < len)
			res[j++] = tmp->content[(*i)++];
		if (j == len && tmp->content[*i])
			break ;
		*i = 0;
		tmp = tmp->next;
	}
	*lst = tmp;
	return (res[j] = '\0', res);
}

static int	ft_task_globbing(t_list **lst, t_list **top, int *i)
{
	int		len;
	int		flag;
	char	*res;
	t_list	*tmp;

	flag = 0;
	tmp = *lst;
	while (tmp)
	{
		if (tmp->content[*i] == 32)
			break ;
		len = ft_len_globbing(tmp, *i, &flag);
		res = ft_str_globbing(&tmp, i, len);
		if (!res)
			return (1);
		ft_listadd_back(top, ft_listnew(res, flag));
		flag = 0;
	}
	*lst = tmp;
	return (0);
}

t_list	*ft_check_globbing(t_list **lst, int *i)
{
	t_list	*top;
	t_list	*tmp;

	if (!lst)
		return (NULL);
	top = NULL;
	tmp = *lst;
	while (tmp)
	{
		while (tmp->content[*i] == 32)
			(*i)++;
		if (tmp->content[*i])
			break ;
		*i = 0;
		tmp = tmp->next;
	}
	if (ft_task_globbing(&tmp, &top, i))
	{
		*lst = NULL;
		return (ft_listclear(&top), NULL);
	}
	*lst = tmp;
	if (!top)
		ft_listadd_back(&top, ft_listnew(ft_strdup(""), 42));
	return (top);
}
