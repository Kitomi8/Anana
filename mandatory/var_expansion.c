/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 06:27:54 by landriam          #+#    #+#             */
/*   Updated: 2025/12/26 16:43:30 by landriam         ###   ########.fr       */
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
	if (tmp[0] == '$' && tmp[1] != '\0')
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

char	*var_expansion(char *str, t_list *lst)
{
	int		squote;
	int		dquote;
	char	*res;
	t_list	*head;

	if (!str)
		return (NULL);
	head = NULL;
	squote = 0;
	dquote = 0;
	while (*str)
	{
		res = change_variable(&str, &squote, &dquote);
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
