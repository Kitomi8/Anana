/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_apply_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 06:27:54 by landriam          #+#    #+#             */
/*   Updated: 2026/01/05 15:56:47 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	ft_error_open(char *str, char *src)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(src, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}

static int	ft_fd_duplicate(int fd, t_nodetype type)
{
	if (type == GREAT || type == DGREAT)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (close(fd), ft_putstr_fd(strerror(errno), 2), 1);
	}
	else
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			return (close(fd), ft_putstr_fd(strerror(errno), 2), 1);
	}
	close(fd);
	return (0);
}

static int	ft_open_red(t_nodetype type, t_list *arg)
{
	int			fd;

	if (type == LESS)
		fd = open(arg->content, O_RDONLY);
	if (type == GREAT)
		fd = open(arg->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (type == DGREAT)
		fd = open(arg->content, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		ft_error_open(strerror(errno), arg->content);
		return (1);
	}
	if (ft_fd_duplicate(fd, type))
		return (1);
	return (0);
}

static int	ft_dless(t_redirect *red, t_here_doc **doc)
{
	int			check;
	t_here_doc	*tmp;

	check = 0;
	tmp = *doc;
	while (tmp)
	{
		if (!ft_strcmp(red->body, tmp->delimiter) && check == red->fd)
		{
			if (ft_fd_duplicate(tmp->fd, red->type))
				return (1);
			break ;
		}
		check++;
		tmp = tmp->next;
	}
	return (0);
}

int	red_apply(t_redirect *head, t_here_doc **doc, t_list *var)
{
	t_list		*arg;
	t_redirect	*tmp;

	if (!head)
		return (0);
	tmp = head;
	while (tmp)
	{
		if (tmp->type != DLESS)
		{
			arg = red_expansion(tmp->body, var);
			if (!arg)
				return (ft_listclear(&arg), 1);
			if (ft_open_red(tmp->type, arg))
				return (ft_listclear(&arg), 1);
			ft_listclear(&arg);
		}
		else
		{
			if (ft_dless(tmp, doc))
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
