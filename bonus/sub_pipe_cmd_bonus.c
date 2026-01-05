/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_pipe_cmd_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 10:41:27 by landriam          #+#    #+#             */
/*   Updated: 2025/12/30 16:26:58 by landriam         ###   ########.fr       */
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

static void	middle_cmd(t_store *store, t_store *all)
{
	int			status;
	t_node		*node;
	t_command	*cmd;
	t_store		sub;

	cmd = store->cmd;
	node = (t_node *)cmd->node;
	sub = (t_store){store->var, store->doc, node, NULL};
	if (red_apply(cmd->redirect, &store->doc, store->var))
		exit(1);
	if (!node)
		exit(0);
	status = execution(&sub, all);
	exit(status);
}

pid_t	sub_cmd_pipe(t_store *store, t_store *all, int *fd)
{
	pid_t	pid;
	int		pipefd[2];

	if (ft_init_pipe(store->cmd, pipefd))
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		if (*fd > 2)
			close(*fd);
		return (perror("fork"), -1);
	}
	if (pid == 0)
	{
		dup_fd(pipefd, *fd);
		middle_cmd(store, all);
	}
	if (*fd > 2)
		close(*fd);
	*fd = pipefd[0];
	if (pipefd[1] > 2)
		close(pipefd[1]);
	return (pid);
}
