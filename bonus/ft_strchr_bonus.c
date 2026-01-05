/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:43:41 by landriam          #+#    #+#             */
/*   Updated: 2025/12/30 16:19:02 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	ft_strchr(const char *s, int c)
{
	unsigned char	u;

	u = (unsigned char)c;
	while (*s)
	{
		if (*s == u)
			return (1);
		s++;
	}
	if (u == '\0')
		return (1);
	return (0);
}
