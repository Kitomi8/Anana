/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtoky-fa <rtoky-fa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:46:17 by rtoky-fa          #+#    #+#             */
/*   Updated: 2025/11/29 16:35:36 by rtoky-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_child_process(pid_t pid, char *path, char **args,  char **envp)
{
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (execve(path, args, envp) == -1)
		{
			perror("execve");
			exit(1);
		}
	}
	else
	{
		waitpid(pid, NULL, 0);
		free(path);
	}
}
void	execute_simple_cmd(char **args, char **envp)
{
	pid_t	pid;
	char	*path;

	path = find_executable(args[0], envp);
	if (!path)
	{
		write(2, "minishell: command not found: ", 30);
		write(2, args[0], ft_strlen(args[0]));
		write(2, "\n", 1);
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	exec_child_process(pid, path, args, envp);
}
