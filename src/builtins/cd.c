/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtoky-fa <rtoky-fa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 09:14:47 by rtoky-fa          #+#    #+#             */
/*   Updated: 2025/12/16 14:22:20 by rtoky-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **args, t_env **env)
{
	char	*path;
	char	cwd[1024];
	char	*old_pwd;

	if (!args[1])
	{
		path = get_env_value(*env, "HOME");
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 1);
			return (1);
		}
	}
	else
	{
		path = args[1];
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (1);
	old_pwd = ft_strdup(cwd);
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		free(old_pwd);
		return (1);
	}
	update_env_var(env, ft_strdup("OLDPWD"), old_pwd);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		update_env_var(env, ft_strdup("PWD"), ft_strdup(cwd));
	}
	return (0);
}
