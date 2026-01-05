/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builting_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 07:59:11 by landriam          #+#    #+#             */
/*   Updated: 2025/12/30 16:10:07 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	ft_error_open(char *str, t_list *arg)
{
	ft_putstr_fd("minishell: ", 2);
	if (arg)
		ft_putstr_fd(arg->content, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}

static int	ft_open_red(t_redirect *tmp, t_list *arg, t_here_doc **doc)
{
	int			fd;
	t_here_doc	*cur;

	if (arg && tmp->type == LESS)
		fd = open(arg->content, O_RDONLY);
	if (arg && tmp->type == GREAT)
		fd = open(arg->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (arg && tmp->type == DGREAT)
		fd = open(arg->content, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (tmp->type == DLESS)
	{
		cur = *doc;
		while (cur)
		{
			if (!ft_strcmp(tmp->body, cur->delimiter))
			{
				fd = cur->fd;
				break ;
			}
			cur = cur->next;
		}
	}
	if (fd == -1)
		return (ft_error_open(strerror(errno), arg), -1);
	return (fd);
}

static int	ft_red(t_redirect *tmp, t_here_doc **doc, t_list *var, int *fds)
{
	int		fd;
	t_list	*arg;

	arg = NULL;
	if (tmp->type != DLESS)
	{
		arg = red_expansion(tmp->body, var);
		if (!arg)
			return (ft_listclear(&arg), 1);
	}
	fd = ft_open_red(tmp, arg, doc);
	if (fd == -1)
		return (ft_listclear(&arg), 1);
	if (tmp->type == LESS || tmp->type == DLESS)
	{
		if (fds[0] > 2)
			close(fds[0]);
		fds[0] = fd;
		return (ft_listclear(&arg), 0);
	}
	if (fds[1] > 2)
		close(fds[1]);
	fds[1] = fd;
	return (ft_listclear(&arg), 0);
}

static int	red(t_redirect *head, t_here_doc **doc, t_list *var, int *fds)
{
	t_redirect	*tmp;

	if (!head)
		return (0);
	tmp = head;
	while (tmp)
	{
		if (ft_red(tmp, doc, var, fds))
		{
			ft_close(fds);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	exec_builting(t_store *store, t_store *all)
{
	int			status;
	int			fds[2];
	t_list		*arg;
	t_command	*cmd;

	status = 0;
	cmd = store->cmd;
	arg = NULL;
	if (cmd->arg)
	{
		arg = arg_expansion(cmd->arg, store->var);
		if (!arg)
			return (1);
	}
	fds[0] = 0;
	fds[1] = 1;
	if (red(cmd->redirect, &store->doc, store->var, fds))
		return (ft_listclear(&arg), 1);
	status = ft_builting(&arg, store, fds, all);
	if (fds[0] > 2)
		close(fds[0]);
	if (fds[1] > 2)
		close(fds[1]);
	return (ft_listclear(&arg), status);
}
