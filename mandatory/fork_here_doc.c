/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_here_doc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 06:08:12 by landriam          #+#    #+#             */
/*   Updated: 2025/12/12 12:04:31 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_fd(t_here_doc **doc)
{
	t_here_doc	*tmp;

	if (!doc || !*doc)
		return ;
	tmp = *doc;
	while (tmp)
	{
		if (tmp->source)
		{
			if (tmp->fd > 2)
				close(tmp->fd);
		}
		tmp = tmp->next;
	}
}

static void	ft_file_fd(char *res, t_here_doc *tmp, t_here_doc **doc)
{
	int	fd;

	fd = open(tmp->source, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		free(res);
		exit(1);
	}
	write(fd, res, ft_strlen(res));
	close(fd);
	free(res);
	close_fd(doc);
	exit(0);
}

static char	*ft_get_data(t_here_doc *tmp, t_list *var)
{
	char	*str;
	char	*res;

	if (tmp->flags == 0)
		str = takeoff_quote(tmp->delimiter);
	else
		str = ft_strdup(tmp->delimiter);
	if (!str)
		return (NULL);
	res = get_heredoc_fd(str, var, tmp->flags);
	free(str);
	str = NULL;
	if (!res)
		return (NULL);
	return (res);
}

static int	fork_here_doc(t_here_doc **doc, t_here_doc *tmp, t_list *var)
{
	int		fd;
	int		status;
	char	*res;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (ft_putstr_fd(strerror(errno), 2), -1);
	if (pid == 0)
	{
		if (signal_heredoc())
			exit(1);
		res = ft_get_data(tmp, var);
		if (!res)
			exit(0);
		ft_file_fd(res, tmp, doc);
	}
	status = ft_wait(&pid, 1);
	if (status)
		return (status);
	fd = open(tmp->source, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd(strerror(errno), 2), 1);
	tmp->fd = fd;
	return (0);
}

int	parse_here_doc(t_here_doc **doc, t_list *var)
{
	int			i;
	int			status;
	char		*res;
	t_here_doc	*tmp;

	if (!doc || !*doc)
		return (0);
	tmp = *doc;
	i = 0;
	while (tmp)
	{
		res = ft_get_file(++i);
		if (!res)
			return (1);
		tmp->source = res;
		status = fork_here_doc(doc, tmp, var);
		if (status)
		{
			if (status == 130)
				write(1, "\n", 1);
			return (status);
		}
		tmp = tmp->next;
	}
	return (0);
}
