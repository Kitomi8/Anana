/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   middle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 10:41:27 by landriam          #+#    #+#             */
/*   Updated: 2025/12/23 07:10:03 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	core_cmd(char *str, t_list *arg, t_list *var)
{
	char	**arr;
	char	**env;

	arr = ft_array_list(arg);
	if (!arr)
		return ;
	env = ft_array_env(var, 2);
	if (!env)
	{
		ft_clear_array(arr);
		return ;
	}
	if (execve(str, arr, env) == -1)
		perror("execve");
	ft_clear_array(arr);
	ft_clear_array(env);
	ft_listclear(&arg);
	free(str);
	exit(1);
}

static t_list	*ft_check_cmd(t_store *store, t_store *all)
{
	t_list		*arg;
	t_command	*cmd;

	cmd = store->cmd;
	arg = arg_expansion(cmd->arg, store->var);
	if (!arg)
		exit(1);
	if (ft_check_builting(arg->content))
	{
		ft_listclear(&arg);
		if (exec_builting(store, all))
			exit(1);
		exit(0);
	}
	return (arg);
}

void	mid_cmd(t_store *store, t_store *all)
{
	t_list		*arg;
	t_data		path;
	t_command	*cmd;

	cmd = store->cmd;
	if (cmd->arg)
		arg = ft_check_cmd(store, all);
	else
	{
		if (exec_builting(store, all))
			exit(1);
		exit(0);
	}
	if (red_apply(cmd->redirect, &store->doc, store->var))
	{
		ft_listclear(&arg);
		exit(1);
	}
	path = get_path(arg->content, store->var);
	if (path.error)
	{
		ft_listclear(&arg);
		exit(path.error);
	}
	core_cmd(path.word, arg, store->var);
}
