/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_all_character.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 10:22:08 by landriam          #+#    #+#             */
/*   Updated: 2025/12/12 15:10:39 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_isquote(char c, int *squote, int *dquote)
{
	if (c == 39 && *dquote % 2 == 0)
		(*squote)++;
	if (c == 34 && *squote % 2 == 0)
		(*dquote)++;
}

int	ft_isnormal_char(char c)
{
	if (c == 95 || (c >= 65 && c <= 90))
		return (1);
	if (c >= 97 && c <= 122)
		return (1);
	return (0);
}

int	ft_isall_char(char c)
{
	if (c == 95 || (c >= 65 && c <= 90))
		return (1);
	if (c >= 97 && c <= 122)
		return (1);
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

int	ft_ismeta_char(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	if (c == '$' || c == '?')
		return (1);
	return (0);
}

int	ft_is_char(char *str)
{
	if (str[0] == '$')
	{
		if (ft_ismeta_char(str[1]) || ft_isnormal_char(str[1]))
			return (1);
	}
	return (0);
}
