/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtoky-fa <rtoky-fa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 09:14:27 by rtoky-fa          #+#    #+#             */
/*   Updated: 2025/12/12 11:15:15 by rtoky-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env_var(t_env **env, char *key, char *value)
{
	t_env	*node;

	node = get_env_node(*env, key);
	if (node)
	{
		free(node->value);
		node->value = value;
		free(key);
	}
	else
	{
		ft_envadd_back(env, ft_envnew(key, value));
	}
}

int	ft_export(t_env **env, char **args)
{
	char	*key;
	char	*value;
	char	*equal_pos;
	int		i;

	if (!args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		equal_pos = ft_strchr(args[i], '=');
		if (equal_pos)
		{
			key = ft_substr(args[i], 0, equal_pos - args[i]);
			value = ft_strdup(equal_pos + 1);
			update_env_var(env, key, value);
		}
		i++;
	}
	return (0);
}
