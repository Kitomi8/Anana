/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:39:10 by landriam          #+#    #+#             */
/*   Updated: 2026/01/05 18:26:02 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_path_env(t_list *var)
{
	char	*str;
	char	**path;

	str = get_variable("$PATH", var);
	if (!str)
		return (NULL);
	if (!*str)
	{
		free(str);
		str = get_pwd();
	}
	path = ft_split(str, ':');
	if (!path)
	{
		free(str);
		return (NULL);
	}
	free(str);
	return (path);
}

static int	ft_check_access(char *str, char *way)
{
	if (access(way, F_OK))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Command not found\n", 2);
		return (127);
	}
	else
	{
		if (access(way, X_OK))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			return (126);
		}
		if (is_directory(str, way))
			return (126);
	}
	return (0);
}

static t_data	ft_check_path(char **path, char *cmd)
{
	int		i;
	char	*way;

	i = 0;
	way = NULL;
	while (path[i])
	{
		way = ft_strjoin(path[i], cmd);
		if (!way)
			return ((t_data){1, NULL});
		if (!access(way, F_OK))
			break ;
		free(way);
		way = NULL;
		i++;
	}
	return ((t_data){0, way});
}

static t_data	ft_path(char *str, t_list *var)
{
	int		nbr;
	char	*cmd;
	char	**path;
	t_data	data;

	cmd = ft_strjoin("/", str);
	if (!cmd)
		return ((t_data){1, NULL});
	path = get_path_env(var);
	if (!path)
		return (free(cmd), (t_data){1, NULL});
	data = ft_check_path(path, cmd);
	if (data.error)
		return (free(cmd), ft_clear_array(path), (t_data){1, NULL});
	if (!data.word)
		data.word = ft_strdup("");
	nbr = ft_check_access(str, data.word);
	if (nbr)
	{
		free(data.word);
		return (free(cmd), ft_clear_array(path), (t_data){nbr, NULL});
	}
	return (free(cmd), ft_clear_array(path), data);
}

t_data	get_path(char *str, t_list *var)
{
	int		nbr;
	char	*cmd;
	t_data	data;

	if (!ft_strcmp("..", str) || !ft_strcmp("", str))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(str, 2);
		return (ft_putstr_fd(": command not found\n", 2), (t_data){127, NULL});
	}
	if (ft_strchr(str, '/'))
	{
		cmd = ft_strdup(str);
		data = (t_data){0, cmd};
		nbr = ft_check_access(str, data.word);
		if (nbr)
			return (free(data.word), (t_data){nbr, NULL});
	}
	else
	{
		data = ft_path(str, var);
		if (!data.word)
			return (data);
	}
	return (data);
}
