/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_cmd_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 10:41:27 by landriam          #+#    #+#             */
/*   Updated: 2025/12/30 16:10:37 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	ft_init_pipe(t_command *cmd, int pipefd[])
{
	if (cmd->next)
	{
		if (pipe(pipefd) == -1)
			return (perror("pipe"), 1);
	}
	else
	{
		pipefd[0] = 0;
		pipefd[1] = 1;
	}
	return (0);
}

static pid_t	fork_cmd(t_store *store, t_store *all, int *fd)
{
	int		pipefd[2];
	pid_t	pid;

	if (ft_init_pipe(store->cmd, pipefd))
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		if (*fd > 2)
			close(*fd);
		return (ft_close(pipefd), perror("fork"), -1);
	}
	if (pid == 0)
	{
		if (default_signal())
			exit(1);
		dup_fd(pipefd, *fd);
		mid_cmd(store, all);
	}
	if (*fd > 2)
		close(*fd);
	*fd = pipefd[0];
	if (pipefd[1] > 2)
		close(pipefd[1]);
	return (pid);
}

static pid_t	exec(t_store *store, t_store *all, int *fd)
{
	pid_t	pid;

	if (store->cmd->type == COMMAND_SIMPLE)
	{
		pid = fork_cmd(store, all, fd);
		if (pid == -1)
			return (-1);
	}
	else
	{
		pid = sub_cmd_pipe(store, all, fd);
		if (pid == -1)
			return (-1);
	}
	return (pid);
}

static pid_t	*core_pipe(t_store *store, t_store *all, int len)
{
	int			i;
	int			fd;
	pid_t		pid;
	pid_t		*pids;
	t_command	*cmd;

	pids = (pid_t *)malloc(sizeof(pid_t) * (len));
	if (!pids)
		return (NULL);
	i = 0;
	fd = 0;
	cmd = store->node->command;
	while (cmd)
	{
		pid = exec(store, all, &fd);
		if (pid == -1)
			return (free(pids), NULL);
		pids[i++] = pid;
		cmd = cmd->next;
		store->cmd = cmd;
	}
	return (pids);
}

int	exec_pipe_cmd(t_store *store, t_store *all)
{
	int		len;
	int		status;
	pid_t	*pids;

	len = lenght_cmd(store->cmd);
	pids = core_pipe(store, all, len);
	if (!pids)
		return (1);
	status = ft_wait(pids, len);
	return (free(pids), status);
}
