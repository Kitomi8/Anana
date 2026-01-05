/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtoky-fa <rtoky-fa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 09:14:20 by rtoky-fa          #+#    #+#             */
/*   Updated: 2025/12/30 16:17:52 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

char	*get_pwd(void)
{
	int		size;
	char	*res;
	char	*buf;

	res = NULL;
	size = 30;
	while (!res)
	{
		buf = NULL;
		res = getcwd(buf, size);
		if (!res)
		{
			if (errno == ERANGE)
				size = size + 10;
			else
			{
				ft_putstr_fd("minishell: ", 2);
				perror("pwd");
				return (NULL);
			}
		}
		free(buf);
	}
	return (res);
}

int	ft_pwd(int fds[2])
{
	char	*res;

	res = get_pwd();
	if (!res)
		return (1);
	ft_putstr_fd(res, fds[1]);
	ft_putstr_fd("\n", fds[1]);
	free(res);
	return (0);
}
