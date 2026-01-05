/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 13:31:02 by landriam          #+#    #+#             */
/*   Updated: 2025/12/30 16:17:39 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	lenght;

	lenght = 0;
	while (s[lenght])
		lenght++;
	write(fd, s, lenght);
}
