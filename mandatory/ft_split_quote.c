/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 23:22:25 by landriam          #+#    #+#             */
/*   Updated: 2025/12/27 17:10:56 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_squote_lenght(char *str)
{
	int	i;
	int	len;
	int	squote;

	i = 0;
	len = 0;
	squote = 0;
	while (str[i])
	{
		if (str[i] == 39)
			squote++;
		if (squote % 2 == 1)
			len++;
		else
		{
			len++;
			if (!(str[i] == 39 && str[i + 1] == 39))
				break ;
		}
		i++;
	}
	return (len);
}

static int	ft_dquote_lenght(char *str)
{
	int	i;
	int	len;
	int	dquote;

	i = 0;
	len = 0;
	dquote = 0;
	while (str[i])
	{
		if (str[i] == 34)
			dquote++;
		if (dquote % 2 == 1)
			len++;
		else
		{
			len++;
			if (!(str[i] == 34 && str[i + 1] == 34))
				break ;
		}
		i++;
	}
	return (len);
}

int	ft_quote_lenght(char *str, int *flag)
{
	int	i;
	int	len;

	len = 0;
	if (str[0] == 39)
		return (*flag = 1, ft_squote_lenght(str));
	if (str[0] == 36 && str[1] == 39)
		return (*flag = 1, ft_squote_lenght(&str[1]));
	if (str[0] == 34)
		return (*flag = 2, ft_dquote_lenght(str));
	if (str[0] == 36 && str[1] == 34)
		return (*flag = 2, ft_dquote_lenght(&str[1]));
	i = 0;
	while (str[i])
	{
		if (str[i] == 39 || str[i] == 34)
			break ;
		if (str[i] == 36 && (str[i + 1] == 39 || str[i + 1] == 34))
			break ;
		len++;
		i++;
	}
	return (len);
}

static char	*ft_quote_word(char *str, int len)
{
	int		i;
	int		j;
	char	*res;

	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	if (str[i] == 36 && (str[i + 1] == 39 || str[i + 1] == 34))
	{
		i++;
		len++;
	}
	while (str[i] && i < len)
	{
		res[j] = str[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (res);
}

t_list	*ft_split_quote(char *str)
{
	int		len;
	int		flag;
	char	*copy;
	char	*res;
	t_list	*top;

	if (!str)
		return (NULL);
	top = NULL;
	copy = str;
	flag = 0;
	while (*copy)
	{
		len = ft_quote_lenght(copy, &flag);
		res = ft_quote_word(copy, len);
		if (!res)
			return (NULL);
		ft_listadd_back(&top, ft_listnew(res, flag));
		if (copy[0] == 36 && (copy[1] == 39 || copy[1] == 34))
			len++;
		copy = copy + len;
		flag = 0;
	}
	return (top);
}
