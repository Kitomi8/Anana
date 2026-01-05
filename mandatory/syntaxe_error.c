/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxe_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 21:27:29 by landriam          #+#    #+#             */
/*   Updated: 2025/11/17 19:47:50 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect_error(t_token *token, char *str)
{
	if (token->type == LESS)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(" `<'\n", 2);
		return ;
	}
	if (token->type == DLESS)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(" `<<'\n", 2);
		return ;
	}
	if (token->type == GREAT)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(" `>'\n", 2);
		return ;
	}
	if (token->type == DGREAT)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(" `>>'\n", 2);
	}
}

static void	control_error(t_token *token, char *str)
{
	if (token->type == PIPE)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(" `|'\n", 2);
	}
	if (token->type == OPEN_PAREN)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(" `('\n", 2);
	}
	if (token->type == CLOSE_PAREN)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(" `)'\n", 2);
	}
	if (token->type == AND)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(" `&&'\n", 2);
	}
	if (token->type == OR)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(" `||'\n", 2);
	}
}

void	syntaxe_error(t_token *token)
{
	char	*str;

	str = "minishell: syntax error near unexpected token";
	if (token->type == WORD)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(" `", 2);
		ft_putstr_fd(token->value, 2);
		ft_putstr_fd("'\n", 2);
		free(token->value);
		return ;
	}
	if (token->type == END)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(" `newline'\n", 2);
		return ;
	}
	redirect_error(token, str);
	control_error(token, str);
}
