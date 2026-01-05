/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_path_cd_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 22:24:05 by landriam          #+#    #+#             */
/*   Updated: 2025/12/30 16:27:41 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static char	*get_parentdir(char *res)
{
	int		i;
	int		len;
	char	*des;

	len = ft_strlen(res);
	i = len - 1;
	while (i > 0)
	{
		if (res[i] == '/' && i != (len - 1))
			break ;
		i--;
	}
	if (i == 0 && res[i] == '/')
	{
		des = ft_strdup("/");
		if (!des)
			return (NULL);
		return (des);
	}
	des = ft_string_dup(res, i);
	if (!des)
		return (NULL);
	return (des);
}

static char	*get_childdir(char *res, char *pwd, char *tmp)
{
	int		len;
	char	*str;
	char	*des;

	if (tmp[0] == '/')
		return (ft_strdup(tmp));
	if (!res)
	{
		str = ft_strjoin(pwd, "/");
		if (!str)
			return (NULL);
		des = ft_strjoin(str, tmp);
		free(str);
		return (des);
	}
	len = ft_strlen(res);
	if (res[len - 1] == '/')
		return (ft_strjoin(res, tmp));
	str = ft_strjoin(res, "/");
	if (!str)
		return (NULL);
	des = ft_strjoin(str, tmp);
	free(str);
	return (des);
}

char	*take_path(char *res, char *pwd, char *tmp)
{
	char	*des;

	if (ft_strcmp("..", tmp) && ft_strcmp("../", tmp))
	{
		des = get_childdir(res, pwd, tmp);
		free(res);
		if (!des)
			return (NULL);
		return (des);
	}
	if (!res)
	{
		des = get_parentdir(pwd);
		if (!des)
			return (NULL);
		return (des);
	}
	des = get_parentdir(res);
	free(res);
	if (!des)
		return (NULL);
	return (des);
}
