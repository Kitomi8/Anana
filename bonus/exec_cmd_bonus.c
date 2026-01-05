/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 10:41:27 by landriam          #+#    #+#             */
/*   Updated: 2025/12/30 16:10:23 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	check_cmd(t_store *store, t_store *all)
{
	int			status;
	t_list		*arg;
	t_command	*cmd;
	t_node		*node;

	node = store->node;
	cmd = node->command;
	if (cmd->arg)
	{
		arg = arg_expansion(cmd->arg, store->var);
		if (!arg)
			return (1);
		if (last_argument(store->var, arg))
			return (ft_listclear(&arg), 1);
		if (ft_check_builting(arg->content))
		{
			status = exec_builting(store, all);
			return (ft_listclear(&arg), status);
		}
		ft_listclear(&arg);
		status = exec_single_cmd(cmd, &store->doc, store->var);
	}
	else
		return (exec_builting(store, all));
	return (status);
}

int	exec_cmd(t_store *store, t_store *all)
{
	int			len;
	int			status;
	t_command	*cmd;
	t_node		*node;

	node = store->node;
	cmd = node->command;
	store->cmd = cmd;
	if (!cmd)
		return (1);
	len = lenght_cmd(cmd);
	if (len == 1)
	{
		if (cmd->type == COMMAND_SIMPLE)
			status = check_cmd(store, all);
		if (cmd->type == COMMAND_COMPOUND)
			status = exec_sub_cmd(store, all);
	}
	else
	{
		status = exec_pipe_cmd(store, all);
		if (status == -1)
			return (1);
	}
	return (status);
}
