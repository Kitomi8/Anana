/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtoky-fa <rtoky-fa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 09:08:52 by rtoky-fa          #+#    #+#             */
/*   Updated: 2025/12/16 14:23:37 by rtoky-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_state	ft_set_state(char quote, t_state state)
{
	if (state == DEFAULT)
	{
		if (quote == '\'')
			return (LINKED);
		if (quote == '\"')
			return (D_QUOTE);
	}
	else if (state == LINKED)
	{
		if (quote == '\'')
			return (DEFAULT);
	}
	else if (state == D_QUOTE)
	{
		if (quote == '\"')
			return (DEFAULT);
	}
	return (state);
}

int	is_separator(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

t_token	*ft_token_new(char *content, t_token_type type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->content = content;
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ft_token_add_back(t_token **lst, t_token *new)
{
	t_token	*curr;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	curr = *lst;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
	new->prev = curr;
}
