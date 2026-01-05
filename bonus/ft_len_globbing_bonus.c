/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len_globbing_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:04:19 by landriam          #+#    #+#             */
/*   Updated: 2025/12/30 16:16:54 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	ft_len_str42(char *str, int *len, int *flag)
{
	int	i;

	i = 0;
	while (str[i] == 42)
	{
		if (str[i] == 42 && str[i + 1] != 42)
			(*flag)++;
		i++;
	}
	while (str[i])
	{
		if (str[i] == 32)
			return (1);
		if (str[i] == 42)
		{
			(*flag)++;
			return (1);
		}
		else
			(*len)++;
		i++;
	}
	return (0);
}

static int	ft_len_str(char *str, int *len)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 32)
			return (1);
		if (str[i] == 42)
			return (1);
		else
			(*len)++;
		i++;
	}
	return (0);
}

static int	ft_len_core42(t_list *lst, int i, int *flag)
{
	int		len;
	char	*str;

	len = 0;
	while (lst)
	{
		if (lst->flag == 0)
		{
			str = lst->content;
			if (ft_len_str42(&str[i], &len, flag))
				return (len);
		}
		else
		{
			str = takeoff_quote(lst->content);
			free(lst->content);
			len += ft_strlen(str);
			lst->content = str;
		}
		i = 0;
		lst = lst->next;
	}
	return (len);
}

static int	ft_len_core(t_list *lst, int i)
{
	int		len;
	char	*str;

	len = 0;
	while (lst)
	{
		if (lst->flag == 0)
		{
			str = lst->content;
			if (str[i] == 32)
				return (len);
			if (ft_len_str(&str[i], &len))
				return (len);
		}
		else
		{
			str = takeoff_quote(lst->content);
			free(lst->content);
			len += ft_strlen(str);
			lst->content = str;
		}
		i = 0;
		lst = lst->next;
	}
	return (len);
}

int	ft_len_globbing(t_list *lst, int i, int *flag)
{
	int		len;
	char	*str;

	if (!lst)
		return (-1);
	str = lst->content;
	if (str[i] == 42)
	{
		len = ft_len_core42(lst, i, flag);
		return (len);
	}
	else
	{
		len = ft_len_core(lst, i);
		return (len);
	}
}
