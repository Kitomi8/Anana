/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 20:11:32 by landriam          #+#    #+#             */
/*   Updated: 2025/12/09 23:18:53 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_meta_character(char *str)
{
	if (*str == ' ' || *str == '\0')
		return (1);
	if (*str == '(' || *str == ')')
		return (1);
	if (*str == '<' || *str == '>')
		return (1);
	if (*str == '|' || (*str == '&' && *(str + 1) == '&'))
		return (1);
	return (0);
}

static int	ft_word_nbr(char *str)
{
	int	i;
	int	dquote;
	int	squote;

	dquote = 0;
	squote = 0;
	i = 0;
	while (str[i])
	{
		ft_isquote(str[i], &squote, &dquote);
		if (squote % 2 == 0 && dquote % 2 == 0)
		{
			if (is_meta_character(&str[i]))
				break ;
		}
		i++;
	}
	if (squote % 2 == 1 || dquote % 2 == 1)
	{
		write(2, "Unclosed quote!\n", 16);
		return (-1);
	}
	return (i);
}

static char	*ft_getvalue_token(char *str, int len)
{
	int		i;
	char	*res;

	i = 0;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	while (str[i] && i < len)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_get_word(char *str, int *lenght)
{
	int		len;
	char	*res;

	if (!str)
		return (NULL);
	len = ft_word_nbr(str);
	*lenght = len;
	if (len == -1)
		return (NULL);
	res = ft_getvalue_token(str, len);
	if (!res)
		return (NULL);
	return (res);
}
