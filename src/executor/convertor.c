/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convertor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtoky-fa <rtoky-fa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 09:43:38 by rtoky-fa          #+#    #+#             */
/*   Updated: 2025/12/16 09:50:56 by rtoky-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_token_list(t_token *tokens)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = tokens;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}


char	**token_to_tab(t_token *tokens)
{
	char	**args;
	int		count;
	int		i;
	t_token	*tmp;

	count = count_token_list(tokens);
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	tmp = tokens;
	i = 0;
	while (tmp)
	{
		args[i] = ft_strdup(tmp->content);
		i++;
		tmp = tmp->next;
	}
	args[i] = NULL; 
	return (args);
}
