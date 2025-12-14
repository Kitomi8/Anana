/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtoky-fa <rtoky-fa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 09:09:21 by rtoky-fa          #+#    #+#             */
/*   Updated: 2025/12/12 10:02:02 by rtoky-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env   *get_env_list(char **envp)
{
    t_env   *env_list;
    int     i;
    char    *key;
    char    *value;
    char    *equal_pos;

    env_list = NULL;
    i = 0;
    while (envp[i])
    {
        equal_pos = ft_strchr(envp[i], '=');
        if (equal_pos)
        {
            key = ft_substr(envp[i], 0, equal_pos - envp[i]);
            value = ft_strdup(equal_pos + 1); 
            ft_envadd_back(&env_list, ft_envnew(key, value));
        }
        i++;
    }
    return (env_list);
}
