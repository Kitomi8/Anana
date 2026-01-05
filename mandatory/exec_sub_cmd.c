/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sub_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 10:41:27 by landriam          #+#    #+#             */
/*   Updated: 2025/12/23 07:10:49 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_fd(t_here_doc **doc)
{
	t_here_doc	*tmp;

	if (!doc || !*doc)
		return ;
	tmp = *doc;
	while (tmp)
	{
		if (tmp->source)
		{
			if (tmp->fd > 2)
				close(tmp->fd);
		}
		tmp = tmp->next;
	}
}

static void	core(t_store *store, t_command *cmd, t_store *all)
{
	int		status;

	if (default_signal())
		exit(1);
	if (red_apply(cmd->redirect, &store->doc, store->var))
		exit(1);
	if (!store->node)
		exit(0);
	status = execution(store, all);
	close_fd(&store->doc);
	exit(status);
}

int	exec_sub_cmd(t_store *store, t_store *all)
{
	int			pid;
	int			wstatus;
	t_command	*cmd;
	t_node		*node;
	t_store		sub;

	cmd = store->node->command;
	node = (t_node *)cmd->node;
	sub = (t_store){store->var, store->doc, node, NULL};
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
		core(&sub, cmd, all);
	wstatus = ft_wait(&pid, 1);
	if (wstatus == -1)
		return (1);
	return (wstatus);
}
