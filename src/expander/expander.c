/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtoky-fa <rtoky-fa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 09:08:33 by rtoky-fa          #+#    #+#             */
/*   Updated: 2025/12/24 16:21:56 by rtoky-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_var_val(char *key, t_env *env)
{
	char	*val;

	if (ft_strcmp(key, "?") == 0)
		return (ft_itoa(g_signal));
	val = get_env_value(env, key);
	if (val)
		return (ft_strdup(val));
	return (ft_strdup(""));
}

static char	*extract_key(char *str, int *i)
{
	int		start;
	char	*key;

	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	key = ft_substr(str, start, *i - start);
	return (key);
}

static void	append_char(char **s, char c)
{
	char	str[2];
	char	*tmp;

	str[0] = c;
	str[1] = 0;
	tmp = ft_strjoin(*s, str);
	free(*s);
	*s = tmp;
}

static void	process_var(char *str, int *i, char **res, t_env *env)
{
	char	*key;
	char	*val;
	char	*tmp;

	key = extract_key(str, i);
	val = get_var_val(key, env);
	tmp = ft_strjoin(*res, val);
	free(*res);
	*res = tmp;
	free(key);
	free(val);
}

static char	*expand_string(char *str, t_env *env)
{
	char	*res;
	int		i;
	int		in_sq;

	i = 0;
	in_sq = 0;
	res = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '\'')
			in_sq = !in_sq;
		if (str[i] == '$' && !in_sq && (ft_isalnum(str[i + 1])
				|| str[i + 1] == '_' || str[i + 1] == '?'))
		{
			process_var(str, &i, &res, env);
		}
		else
		{
			append_char(&res, str[i]);
			i++;
		}
	}
	return (res);
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

void	ft_expand(t_token *tokens, t_env *env)
{
	t_token	*curr;
	char	*tmp;

	curr = tokens;
	while (curr)
	{
		if (curr->type == WORD)
		{
			tmp = expand_string(curr->content, env);
			free(curr->content);
			curr->content = remove_quotes(tmp);
		}
		curr = curr->next;
	}
}
