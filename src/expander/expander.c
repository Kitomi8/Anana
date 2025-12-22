/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtoky-fa <rtoky-fa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 09:08:33 by rtoky-fa          #+#    #+#             */
/*   Updated: 2025/12/22 15:16:26 by rtoky-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_var_value(char *var_name, t_env *env)
{
	char	*value;

	if (ft_strcmp(var_name, "?") == 0)
	{
		return (ft_itoa(g_signal)); 
	}
	value = get_env_value(env, var_name);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

static char	*extract_var_name(char *str, int *i)
{
	int		start;
	char	*var_name;

	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	var_name = ft_substr(str, start, *i - start);
	return (var_name);
}

static char	*expand_string(char *str, t_env *env)
{
	char	*new_str;
	char	*tmp;
	char	*var_name;
	char	*var_value;
	int		i;
	// int		start;
	int		in_s_quote;

	new_str = ft_strdup("");
	i = 0;
	in_s_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			in_s_quote = !in_s_quote;
		else if (str[i] == '\"' && !in_s_quote)
			;

		if (str[i] == '$' && !in_s_quote && (ft_isalnum(str[i + 1]) || str[i + 1] == '_' || str[i + 1] == '?'))
		{
			var_name = extract_var_name(str, &i);
			var_value = get_var_value(var_name, env);
			tmp = ft_strjoin(new_str, var_value);
			free(new_str);
			free(var_name);
			free(var_value);
			new_str = tmp;
			continue ;
		} 
		char c[2] = {str[i], 0};
		tmp = ft_strjoin(new_str, c);
		free(new_str);
		new_str = tmp;
		i++;
	}
	return (new_str);
}

char	*remove_quotes(char *str)
{
	char	*new_str;
	int		len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len < 2)
		return (str);
	if ((str[0] == '\'' && str[len - 1] == '\'') || (str[0] == '\"' && str[len
			- 1] == '\"'))
	{
		new_str = ft_substr(str, 1, len - 2);
		free(str);
		return (new_str);
	}
	return (str);
}
void	ft_expand(t_token *token_list, t_env *env)
{
	t_token	*curr;
	char	*expanded;

	curr = token_list;
	while (curr)
	{
		if (curr->type == WORD)
		{
		
			expanded = expand_string(curr->content, env);
			free(curr->content);
			
			curr->content = remove_quotes(expanded);
		}
		curr = curr->next;
	}
}

