/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builting_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:35:54 by landriam          #+#    #+#             */
/*   Updated: 2025/12/30 16:13:54 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	ft_builting(t_list **lst, t_store *store, int fds[2], t_store *all)
{
	int		status;
	t_list	*arg;

	status = 0;
	arg = *lst;
	if (!arg)
		return (0);
	if (!ft_strcmp("echo", arg->content))
		echo(arg, fds);
	if (!ft_strcmp("env", arg->content))
		env(&store->var, fds);
	if (!ft_strcmp("exit", arg->content))
		status = ft_exit(lst, store, all, fds);
	if (!ft_strcmp("export", arg->content))
		status = ft_export(arg, &store->var, fds);
	if (!ft_strcmp("unset", arg->content))
		status = ft_unset(arg, &store->var);
	if (!ft_strcmp("pwd", arg->content))
		ft_pwd(fds);
	if (!ft_strcmp("cd", arg->content))
		status = current_dir(arg, &store->var);
	return (status);
}
