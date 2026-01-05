/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 16:26:57 by landriam          #+#    #+#             */
/*   Updated: 2025/12/12 16:41:47 by landriam         ###   ########.fr       */
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
			close(tmp->fd);
			unlink(tmp->source);
		}
		tmp = tmp->next;
	}
}

void	clear_all(t_store *store)
{
	clear_node(&store->node);
	close_fd(&store->doc);
	clear_here_doc(&store->doc);
	ft_listclear(&store->var);
}
