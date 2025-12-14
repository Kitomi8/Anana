/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtoky-fa <rtoky-fa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 19:50:39 by rtoky-fa          #+#    #+#             */
/*   Updated: 2025/12/12 11:11:01 by rtoky-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_paths_from_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			return (ft_split(envp[i] + 5, ':'));
		}
		i++;
	}
	return (NULL);
}

char	*find_executable(char *cmd, char **envp)
{
	char	**paths;
	char	*path_temp;
	char	*final_path;
	int		i;

	if (!cmd || !cmd[0])
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	paths = get_paths_from_env(envp);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		path_temp = ft_strjoin(paths[i], "/");
		final_path = ft_strjoin(path_temp, cmd);
		free(path_temp);
		if (access(final_path, F_OK | X_OK) == 0)
		{
			free_tab(paths);
			return (final_path);
		}
		// printf("%s  \n", final_path);
		free(final_path);
		i++;
	}
	free_tab(paths);
	return (NULL);
}
