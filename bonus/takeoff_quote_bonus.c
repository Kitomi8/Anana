/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   takeoff_quote_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 13:17:13 by landriam          #+#    #+#             */
/*   Updated: 2025/12/30 16:27:28 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	is_quote(char c, int *squote, int *dquote)
{
	if (c == 34 && (*squote % 2 == 0))
		(*dquote)++;
	if (c == 39 && (*dquote % 2 == 0))
		(*squote)++;
}

static int	count_string(char *str, int *squote, int *dquote)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		is_quote(str[i], squote, dquote);
		if (*squote % 2 == 0 && *dquote % 2 == 0)
		{
			if (str[i] != 39 && str[i] != 34)
				len++;
		}
		else
		{
			if (*dquote % 2 == 1 && str[i] != 34)
				len++;
			if (*squote % 2 == 1 && str[i] != 39)
				len++;
		}
		i++;
	}
	return (len);
}

static void	take_string(char *str, char *res, int *squote, int *dquote)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		is_quote(str[i], squote, dquote);
		if (*squote % 2 == 0 && *dquote % 2 == 0)
		{
			if (str[i] != 39 && str[i] != 34)
				res[len++] = str[i];
		}
		else
		{
			if (*dquote % 2 == 1 && str[i] != 34)
				res[len++] = str[i];
			if (*squote % 2 == 1 && str[i] != 39)
				res[len++] = str[i];
		}
		i++;
	}
	res[len] = '\0';
}

char	*takeoff_quote(char *str)
{
	int		len;
	int		squote;
	int		dquote;
	char	*res;

	if (!str)
		return (NULL);
	squote = 0;
	dquote = 0;
	len = count_string(str, &squote, &dquote);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	squote = 0;
	dquote = 0;
	take_string(str, res, &squote, &dquote);
	return (res);
}
