/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_function_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 06:12:20 by landriam          #+#    #+#             */
/*   Updated: 2025/12/30 16:28:37 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static t_list	*ft_listlast(t_list *lst)
{
	t_list	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	exit_status(t_list *var, int nbr)
{
	char	*str;

	str = ft_itoa(nbr);
	if (!str)
		return ;
	assign_variable(var, "?", str);
	free(str);
}

int	last_argument(t_list *var, t_list *arg)
{
	int		nbr;
	t_list	*cur;
	t_list	*tmp;

	tmp = var;
	while (tmp)
	{
		if (!ft_string_cmp("_", tmp->content))
		{
			cur = ft_listlast(arg);
			nbr = assign_variable(var, "_", cur->content);
			if (nbr == -1)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
