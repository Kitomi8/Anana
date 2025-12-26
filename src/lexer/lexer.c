/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtoky-fa <rtoky-fa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 09:08:49 by rtoky-fa          #+#    #+#             */
/*   Updated: 2025/12/26 11:24:24 by rtoky-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token_type	get_type(char *str)
{
	if (ft_strcmp(str, "|") == 0)
		return (PIPE);
	if (ft_strcmp(str, "<") == 0)
		return (INPUT);
	if (ft_strcmp(str, ">") == 0)
		return (trunc);
	if (ft_strcmp(str, "<<") == 0)
		return (APPEND);
	if (ft_strcmp(str, ">>") == 0)
		return (HEREDOC);
	return (WORD);
}
static int	handle_token(char *line, int i, t_token **token_list)
{
	t_token_type	type;
	char	*content;
	int		len;

	len = 1;
	if ((line[i] == '>' && line[i + 1] == '>') || (line[i] == '<' && line[i + 1] == '<'))
		len = 2;
	content = ft_substr(line, i, len);
	type = get_type(content);
	ft_token_add_back(token_list, ft_token_new(content, type));
	return (len);
}

static int handle_word(char *line, int i, t_token **token_list)
{
	int start;
	t_state state;
	char *content;

	start = i;
	state = DEFAULT;
	while (line[i])
	{
		state = ft_set_state(line[i], state);
		if (state == DEFAULT && (is_separator(line[i])
				|| line[i] == '|' || line[i] == '<' || line[i] == '>'))
			break;
		i++;
	}
	content = ft_substr(line,start, start - i);
	ft_token_add_back(token_list, ft_token_new(content, WORD));
	return (i - start);
}

t_token	*ft_lexer(char *line)
{
	t_token	*token_list;
	int		i;
	
	token_list = NULL;
	i = 0;
	while (line[i])
	{
		if (is_separator(line[i]))
			i++;
		else if (line[i] == '|' || line[i] == '<' || line[i] == '>')
			i += handle_token(line, i, &token_list);
		else
			i += handle_word(line, i, &token_list);
	}
	
	return (token_list);
}
