/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_variable_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 22:13:20 by landriam          #+#    #+#             */
/*   Updated: 2025/12/30 16:07:38 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	ft_isnot_dollar(char *str, int *squote, int *dquote)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		ft_isquote(str[i], squote, dquote);
		if (*squote % 2 == 0)
		{
			if (str[i] != '$')
				len++;
			else
			{
				if (ft_ismeta_char(str[i + 1]) || ft_isnormal_char(str[i + 1]))
					break ;
				else
					len++;
			}
		}
		else
			len++;
		i++;
	}
	return (len);
}

static int	ft_is_dollar(char *str)
{
	int	i;

	i = 1;
	if (ft_ismeta_char(str[1]))
		return (2);
	if (ft_isnormal_char(str[1]))
	{
		i++;
		while (str[i])
		{
			if (!ft_isall_char(str[i]))
				break ;
			i++;
		}
	}
	return (i);
}

static int	ft_word_count(char *str, int *squote, int *dquote)
{
	if (!str)
		return (-1);
	if (!*str)
		return (0);
	if (str[0] != '$')
		return (ft_isnot_dollar(str, squote, dquote));
	else
	{
		if (str[1] == '\0')
			return (1);
		return (ft_is_dollar(str));
	}
}

static char	*ft_get_str(char *str, int len)
{
	int		i;
	char	*res;

	if (!str)
		return (NULL);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (str[i] && i < len)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*change_variable(char **str, int *squote, int *dquote)
{
	int		len;
	char	*src;
	char	*res;

	if (!str || !*str)
		return (NULL);
	src = *str;
	len = ft_word_count(src, squote, dquote);
	if (len < 0)
		return (NULL);
	res = ft_get_str(src, len);
	if (!res)
		return (NULL);
	*str = src + len;
	return (res);
}
