/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_globbing_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:02:56 by landriam          #+#    #+#             */
/*   Updated: 2025/12/30 16:15:28 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	ft_check_entry(char *entry, t_list *lst)
{
	int		len;
	t_list	*tmp;
	char	*str;

	len = 0;
	tmp = lst;
	while (tmp)
	{
		str = tmp->content;
		if (!*str && tmp->flag == 1)
			break ;
		if (ft_cmp_entry(tmp->flag, entry, str, &len))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

static char	*ft_check_file(char *entry, t_list *lst)
{
	int	flag;

	flag = 0;
	if (lst->flag == 2 || lst->flag == 1)
		flag = 1;
	if (flag)
	{
		if (entry[0] != '.')
		{
			if (!ft_check_entry(entry, lst))
				return (ft_strdup(entry));
		}
	}
	else
	{
		if (!ft_check_entry(entry, lst))
			return (ft_strdup(entry));
	}
	return (ft_strdup(""));
}

static int	ft_core_globbing(t_list **head, t_list *lst)
{
	char			*res;
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	if (!dir)
		return (ft_putstr_fd(strerror(errno), 2), 1);
	entry = readdir(dir);
	while (entry)
	{
		res = ft_check_file(entry->d_name, lst);
		if (!res)
			return (closedir(dir), 1);
		if (!*res)
			free(res);
		else
			ft_listadd_back(head, ft_listnew(res, -1));
		entry = readdir(dir);
	}
	if (errno != 0)
		return (closedir(dir), ft_putstr_fd(strerror(errno), 2), 1);
	closedir(dir);
	return (0);
}

static int	ft_check_flag(t_list **head, t_list *lst)
{
	if (lst->flag == 1)
	{
		if (!lst->content[0])
		{
			if (ft_all_globbing(head))
				return (1);
		}
		else
		{
			if (ft_core_globbing(head, lst))
				return (1);
		}
	}
	else
	{
		if (lst->flag != 42)
		{
			ft_listadd_back(head, ft_listnew(lst->content, -1));
			lst->content = NULL;
		}
	}
	return (0);
}

t_list	*ft_get_globbing(t_list *lst)
{
	t_list	*head;

	head = NULL;
	if (lenght_list(lst) == 1)
	{
		if (ft_check_flag(&head, lst))
			return (ft_listclear(&head), NULL);
	}
	else
	{
		if (ft_core_globbing(&head, lst))
			return (ft_listclear(&head), NULL);
	}
	if (!head)
		ft_listadd_back(&head, ft_listnew(ft_strdup(""), 0));
	return (head);
}
