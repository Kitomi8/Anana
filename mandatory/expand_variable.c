/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 22:13:20 by landriam          #+#    #+#             */
/*   Updated: 2025/11/06 11:06:30 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_var(char **res, t_list *lst, t_list **head)
{
	char	*var;
	char	*tmp;

	tmp = *res;
	if (!tmp)
		return (1);
	var = NULL;
	if (tmp[0] == '$')
	{
		var = get_variable(tmp, lst);
		free(tmp);
		*res = NULL;
		if (!var)
			return (1);
		ft_listadd_back(head, ft_listnew(var, -1));
	}
	else
		ft_listadd_back(head, ft_listnew(tmp, -1));
	return (0);
}

char	*expand_variable(char *str, t_list *lst)
{
	char	*res;
	char	*copy;
	t_list	*head;

	if (!str)
		return (NULL);
	head = NULL;
	copy = str;
	while (*copy)
	{
		res = take_variable(&copy);
		if (ft_check_var(&res, lst, &head))
		{
			ft_listclear(&head);
			return (NULL);
		}
	}
	res = ft_linkedlst_string(head);
	ft_listclear(&head);
	return (res);
}
