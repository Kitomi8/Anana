/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtoky-fa <rtoky-fa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 09:08:49 by rtoky-fa          #+#    #+#             */
/*   Updated: 2025/12/16 14:24:17 by rtoky-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_lexer(char *line)
{
	t_token	*token_list;
	int		i;
	int		start;
	t_state	state;
	char	*word;

	token_list = NULL;
	state = DEFAULT;
	i = 0;
	while (line)
	{
		while (line[i] && is_separator(line[i]))
			i++;
		if (!line[i])
			break ;
		start = i;
		while (line[i])
		{
			state = ft_set_state(line[i], state);
			if (state == DEFAULT && is_separator(line[i]))
				break ;
			i++;
		}
		word = ft_substr(line, start, i - start);
		ft_token_add_back(&token_list, ft_token_new(word, WORD));
	}
	return (token_list);
}
