/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 10:41:27 by landriam          #+#    #+#             */
/*   Updated: 2025/12/24 09:41:45 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execution(t_store *store, t_store *all)
{
	int		status;
	t_store	left;
	t_store	right;

	if (!store)
		return (exit_status(store->var, 0), 0);
	if (store->node->command)
	{
		status = exec_cmd(store, all);
		return (exit_status(store->var, status), status);
	}
	left = (t_store){store->var, store->doc, store->node->left, NULL};
	right = (t_store){store->var, store->doc, store->node->right, NULL};
	status = execution(&left, all);
	if (!status && store->node->type == AND)
	{
		status = execution(&right, all);
		return (exit_status(store->var, status), status);
	}
	if (status && store->node->type == OR)
		status = execution(&right, all);
	exit_status(store->var, status);
	return (status);
}
