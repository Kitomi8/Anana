/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 11:47:19 by landriam          #+#    #+#             */
/*   Updated: 2025/12/30 16:13:39 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	ft_atoi(const char *nptr)
{
	int	value;
	int	s;

	value = 0;
	s = 0;
	while (*nptr == 32 || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == 45 || *nptr == 43)
	{
		if (*nptr == 45)
			s++;
		nptr++;
	}
	while (*nptr >= 48 && *nptr <= 57)
	{
		value = (*nptr - '0') + 10 * value;
		nptr++;
	}
	if (s)
		value = -value;
	return (value);
}
