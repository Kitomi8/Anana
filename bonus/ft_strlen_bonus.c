/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 14:41:08 by landriam          #+#    #+#             */
/*   Updated: 2025/12/30 16:19:54 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	ft_strlen(const char *str)
{
	int	lenght;

	lenght = 0;
	if (!str)
		return (-1);
	while (str[lenght])
		lenght++;
	return (lenght);
}
