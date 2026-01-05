/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   current_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 22:24:05 by landriam          #+#    #+#             */
/*   Updated: 2025/12/26 16:42:33 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	dir_path(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '.' && i < 2)
		{
			if (str[i + 1] == '\0')
				return (i + 1);
			if (str[i + 1] == '/')
				return (i + 2);
		}
		if (str[i] == '/')
			return (i + 1);
		i++;
	}
	return (i);
}

static char	*get_path_cd(char *res, char *str, char *pwd, int len)
{
	char	*tmp;

	tmp = ft_string_dup(str, len);
	if (!tmp)
		return (NULL);
	if (ft_strcmp(".", tmp) && ft_strcmp("./", tmp))
	{
		res = take_path(res, pwd, tmp);
		if (!res)
			return (free(tmp), NULL);
	}
	else
	{
		if (!res)
		{
			res = ft_strdup(pwd);
			if (!res)
				return (free(tmp), NULL);
		}
	}
	free(tmp);
	return (res);
}

static char	*get_directory(char *str, t_list **var)
{
	int		i;
	int		len;
	char	*pwd;
	char	*res;

	pwd = get_pwd();
	if (!pwd)
		return (NULL);
	if (!assign_variable(*var, "OLDPWD", pwd))
		ft_listadd_back(var, ft_listnew(ft_strjoin("OLDPWD=", pwd), 2));
	i = 0;
	res = NULL;
	while (str[i])
	{
		len = dir_path(&str[i]);
		res = get_path_cd(res, &str[i], pwd, len);
		if (!res)
			return (free(pwd), NULL);
		i = i + len;
	}
	free(pwd);
	return (res);
}

static int	change_dir(t_list **var)
{
	char	*home;

	home = check_env("HOME", *var);
	if (!home)
		return (1);
	if (!*home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (free(home), 1);
	}
	if (chdir(home) == -1)
	{
		free(home);
		ft_putstr_fd("minishell: ", 2);
		perror("cd");
		return (1);
	}
	assign_variable(*var, "PWD", home);
	return (free(home), 0);
}

int	current_dir(t_list *arg, t_list **var)
{
	char	*str;
	t_list	*tmp;

	tmp = arg->next;
	if (!tmp)
		return (change_dir(var));
	if (tmp->next)
	{
		ft_putstr_fd("minishell: cd: too many arguments", 2);
		return (1);
	}
	if (!*tmp->content)
		return (0);
	str = get_directory(tmp->content, var);
	if (!str)
		return (1);
	if (chdir(str) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		perror(tmp->content);
		return (free(str), 1);
	}
	assign_variable(*var, "PWD", str);
	return (free(str), 0);
}
