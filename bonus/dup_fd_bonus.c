/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_fd_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 07:57:49 by landriam          #+#    #+#             */
/*   Updated: 2025/12/30 16:09:20 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	ft_close(int *pipefd)
{
	if (pipefd[0] > 2)
	{
		close(pipefd[0]);
		pipefd[0] = 0;
	}
	if (pipefd[1] > 2)
	{
		close(pipefd[1]);
		pipefd[1] = 1;
	}
}

void	dup_fd(int *pipefd, int fd)
{
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		ft_close(pipefd);
		if (fd > 2)
			close(fd);
		ft_putstr_fd(strerror(errno), 2);
		exit(1);
	}
	if (fd > 2)
		close(fd);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		ft_close(pipefd);
		ft_putstr_fd(strerror(errno), 2);
		exit(1);
	}
	ft_close(pipefd);
}
