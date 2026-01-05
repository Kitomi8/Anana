/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 10:41:27 by landriam          #+#    #+#             */
/*   Updated: 2025/12/30 16:10:54 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	core_cmd(char *str, t_list *arg, t_list *var)
{
	char	**arr;
	char	**env;

	arr = ft_array_list(arg);
	if (!arr)
		return (-1);
	env = ft_array_env(var, 2);
	if (!env)
	{
		ft_clear_array(arr);
		return (-1);
	}
	if (execve(str, arr, env) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror("execve");
	}
	ft_clear_array(arr);
	ft_clear_array(env);
	return (126);
}

static void	ft_mid_cmd(t_command *cmd, t_here_doc **doc, t_list *var)
{
	int			err;
	t_list		*arg;
	t_data		path;

	if (red_apply(cmd->redirect, doc, var))
		exit(1);
	arg = arg_expansion(cmd->arg, var);
	if (!arg)
		exit(1);
	path = get_path(arg->content, var);
	if (path.error)
	{
		ft_listclear(&arg);
		exit(path.error);
	}
	err = core_cmd(path.word, arg, var);
	ft_listclear(&arg);
	free(path.word);
	if (err == -1)
		exit(1);
	exit(err);
}

int	exec_single_cmd(t_command *cmd, t_here_doc **doc, t_list *var)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		if (default_signal())
			exit(1);
		ft_mid_cmd(cmd, doc, var);
	}
	status = ft_wait(&pid, 1);
	if (status == -1)
		return (1);
	return (status);
}
