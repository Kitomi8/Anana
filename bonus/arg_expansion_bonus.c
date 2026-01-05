/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_expansion_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 06:27:54 by landriam          #+#    #+#             */
/*   Updated: 2025/12/30 16:07:03 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	ft_check_dollar(char *str)
{
	int	i;
	int	squote;
	int	dquote;

	i = 0;
	squote = 0;
	dquote = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		ft_isquote(str[i], &squote, &dquote);
		if (squote % 2 == 0)
		{
			if (str[i] == '$')
			{
				if (ft_ismeta_char(str[i + 1]))
					return (1);
				if (ft_isnormal_char(str[i + 1]))
					return (1);
			}
		}
		i++;
	}
	return (0);
}

static int	core_expansion(t_list *top, t_list *var)
{
	char	*res;
	t_list	*tmp;

	tmp = top;
	while (tmp)
	{
		if (ft_check_dollar(tmp->content))
		{
			res = var_expansion(tmp->content, var);
			if (!res)
				return (1);
			free(tmp->content);
			tmp->content = res;
		}
		tmp = tmp->next;
	}
	return (0);
}

static int	ft_get_argument(t_list **arg, char *word, t_list *var)
{
	t_list	*top;
	t_list	*head;

	top = ft_split_quote(word);
	if (!top)
		return (1);
	if (ft_check_dollar(word))
	{
		if (core_expansion(top, var))
			return (ft_listclear(&top), 1);
	}
	if (lenght_list(top) == 1 && !top->content[0])
		return (ft_listclear(&top), 0);
	head = ft_globbing(top);
	if (!head)
		return (ft_listclear(&top), 1);
	ft_listadd_back(arg, head);
	ft_listclear(&top);
	return (0);
}

t_list	*arg_expansion(t_wordlist *head, t_list *var)
{
	t_list		*arg;
	t_wordlist	*tmp;

	if (!head)
		return (NULL);
	arg = NULL;
	tmp = head;
	while (tmp)
	{
		if (ft_get_argument(&arg, tmp->word, var))
			return (ft_listclear(&arg), NULL);
		tmp = tmp->next;
	}
	return (arg);
}
