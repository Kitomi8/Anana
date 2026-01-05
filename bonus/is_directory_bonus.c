/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_directory_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 09:26:50 by landriam          #+#    #+#             */
/*   Updated: 2025/12/30 16:22:20 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	is_directory(char *str, char *way)
{
	struct stat	sb;

	if (stat(way, &sb) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror("stat");
		return (0);
	}
	if ((sb.st_mode & S_IFMT) == S_IFDIR)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(" : Is a directory\n", 2);
		return (1);
	}
	return (0);
}
