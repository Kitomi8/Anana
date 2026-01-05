/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_globbing_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:03:34 by landriam          #+#    #+#             */
/*   Updated: 2025/12/30 16:16:24 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	ft_check_star(t_list *lst, int i)
{
	char	*str;
	t_list	*tmp;

	tmp = lst;
	str = tmp->content;
	while (str[i] == 32)
		i++;
	while (tmp)
	{
		if (tmp->flag == 0)
		{
			str = tmp->content;
			while (str[i])
			{
				if (str[i] == 42)
					return (1);
				if (str[i] == 32)
					return (0);
				i++;
			}
		}
		i = 0;
		tmp = tmp->next;
	}
	return (0);
}

static int	ft_res_globbing(t_list **arg, t_list *lst, char *str)
{
	t_list	*head;

	head = ft_get_globbing(lst);
	if (!head)
		return (1);
	if (!head->flag)
	{
		if (!*arg)
		{
			free(head->content);
			head->content = ft_strdup(str);
		}
		else
		{
			free(head->content);
			free(head);
			head = NULL;
		}
	}
	ft_listadd_back(arg, head);
	return (0);
}

t_list	*ft_globbing(t_list *top)
{
	int		i;
	char	*str;
	t_list	*lst;
	t_list	*tmp;
	t_list	*arg;

	i = 0;
	str = NULL;
	arg = NULL;
	tmp = top;
	while (tmp)
	{
		if (ft_check_star(tmp, i))
			str = ft_get_star(tmp, i);
		lst = ft_check_globbing(&tmp, &i);
		if (!lst)
			return (ft_listclear(&arg), NULL);
		if (ft_res_globbing(&arg, lst, str))
			return (ft_listclear(&arg), ft_listclear(&lst), NULL);
		free(str);
		str = NULL;
		ft_listclear(&lst);
	}
	return (arg);
}
