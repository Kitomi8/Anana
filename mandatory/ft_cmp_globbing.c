/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmp_globbing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:02:30 by landriam          #+#    #+#             */
/*   Updated: 2025/12/09 23:17:10 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmp_first(char *entry, char *str, int *len)
{
	int	lenght1;
	int	lenght2;

	lenght1 = ft_strlen(entry);
	lenght2 = ft_strlen(str);
	if (lenght1 < lenght2)
		return (1);
	else
	{
		if (ft_string_cmp(entry, str))
			return (1);
		*len += lenght2;
	}
	return (0);
}

int	ft_cmp_last(char *entry, char *str, int *len)
{
	int	lenght1;
	int	lenght2;
	int	nbr;

	lenght1 = ft_strlen(entry);
	lenght2 = ft_strlen(str);
	if (lenght1 < lenght2)
		return (1);
	else
	{
		nbr = lenght1 - lenght2;
		if (ft_string_cmp(entry + nbr, str))
			return (1);
		*len += lenght2;
	}
	return (0);
}

int	ft_cmp_middle(char *entry, char *str, int *len)
{
	int	lenght1;
	int	lenght2;
	int	i;

	lenght1 = ft_strlen(entry);
	lenght2 = ft_strlen(str);
	i = 0;
	if (lenght1 < lenght2)
		return (1);
	else
	{
		while ((lenght1 - i) >= lenght2)
		{
			if (!ft_string_cmp(entry + i, str))
			{
				*len += lenght2 + i;
				return (0);
			}
			i++;
		}
		return (1);
	}
	return (0);
}

int	ft_cmp_entry(int flag, char *entry, char *str, int *len)
{
	if (!flag)
	{
		if (ft_cmp_first(entry + *len, str, len))
			return (1);
	}
	else if (flag == 1)
	{
		if (ft_cmp_last(entry + *len, str, len))
			return (1);
	}
	else
	{
		if (ft_cmp_middle(entry + *len, str, len))
			return (1);
	}
	return (0);
}

int	ft_all_globbing(t_list **head)
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
		if (entry->d_name[0] != '.')
		{
			res = ft_strdup(entry->d_name);
			if (!res)
				return (closedir(dir), 1);
			ft_listadd_back(head, ft_listnew(res, -1));
		}
		entry = readdir(dir);
	}
	if (errno != 0)
		return (closedir(dir), ft_putstr_fd(strerror(errno), 2), 1);
	closedir(dir);
	return (0);
}
