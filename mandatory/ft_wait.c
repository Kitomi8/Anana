/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 23:24:29 by landriam          #+#    #+#             */
/*   Updated: 2025/12/24 17:22:15 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_status(pid_t *pid1, pid_t *pid2, int *count)
{
	int		status;
	int		wstatus;
	pid_t	pid;

	status = 0;
	pid = waitpid(*pid1, &wstatus, WNOHANG);
	if (pid == -1)
		return (ft_putstr_fd(strerror(errno), 2), -1);
	if (pid)
	{
		if (WIFEXITED(wstatus))
		{
			if (*pid1 == *pid2)
				status = WEXITSTATUS(wstatus);
		}
		if (WIFSIGNALED(wstatus))
		{
			if (*pid1 == *pid2)
				status = WTERMSIG(wstatus) + 128;
		}
		*pid1 = 0;
		(*count)++;
	}
	return (status);
}

static int	ft_core_wait(pid_t *pids, int *count, int len)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < len)
	{
		if (pids[i])
		{
			status = ft_status(&pids[i], &pids[len -1], count);
			if (status == -1)
				return (-1);
		}
		i++;
	}
	return (status);
}

int	ft_wait(pid_t *pids, int len)
{
	int	count;
	int	status;
	int	wstatus;

	wstatus = 0;
	count = 0;
	while (1)
	{
		status = ft_core_wait(pids, &count, len);
		if (status == -1)
			return (-1);
		if (status)
			wstatus = status;
		if (g_sig)
			g_sig = 0;
		if (count == len)
			break ;
	}
	return (wstatus);
}
