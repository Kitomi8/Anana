/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 17:28:43 by landriam          #+#    #+#             */
/*   Updated: 2025/12/10 08:47:03 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_nodetype	ft_token_type(char *str)
{
	if (*str == '(')
		return (OPEN_PAREN);
	if (*str == ')')
		return (CLOSE_PAREN);
	if (*str == '&')
	{
		if (*(str + 1) == '&')
			return (AND);
	}
	return (WORD);
}

static t_nodetype	ft_gettype_token(char *str)
{
	if (*str == '\0')
		return (END);
	if (*str == '<')
	{
		if (*(str + 1) == '<')
			return (DLESS);
		return (LESS);
	}
	if (*str == '>')
	{
		if (*(str + 1) == '>')
			return (DGREAT);
		return (GREAT);
	}
	if (*str == '|')
	{
		if (*(str + 1) == '|')
			return (OR);
		return (PIPE);
	}
	return (ft_token_type(str));
}

static int	ft_lenght(t_nodetype type)
{
	if (type == OPEN_PAREN || type == CLOSE_PAREN)
		return (1);
	if (type == LESS || type == GREAT || type == PIPE)
		return (1);
	if (type == DGREAT || type == DLESS)
		return (2);
	if (type == AND || type == OR)
		return (2);
	return (0);
}

t_token	lexer(char **src)
{
	int			i;
	int			lenght;
	char		*res;
	char		*str;
	t_nodetype	type;

	i = 0;
	lenght = 0;
	res = NULL;
	str = *src;
	while (str[i] == ' ')
		i++;
	type = ft_gettype_token(str + i);
	if (type == WORD)
	{
		res = ft_get_word(str + i, &lenght);
		if (!res)
			return ((t_token){ERROR, NULL});
	}
	else
		lenght = ft_lenght(type);
	*src = (str + (i + lenght));
	return ((t_token){type, res});
}
