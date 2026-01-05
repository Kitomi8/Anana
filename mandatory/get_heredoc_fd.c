/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_heredoc_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 05:37:01 by landriam          #+#    #+#             */
/*   Updated: 2025/12/24 17:45:09 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_get_line(char *str)
{
	char	*input;

	input = readline("> ");
	if (!input)
	{
		ft_putstr_fd("minishell: warning: here-document delimited ", 2);
		ft_putstr_fd("by end-of-file (wanted `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("')\n", 2);
		return (NULL);
	}
	if (!ft_strcmp(str, input))
		return (free(input), NULL);
	return (input);
}

static int	ft_check_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (ft_ismeta_char(str[i + 1]) || ft_isnormal_char(str[i + 1]))
				return (1);
		}
		i++;
	}
	return (0);
}

static char	*switch_variable(char **res, t_list *var, int flag)
{
	char	*des;
	char	*tmp;

	tmp = *res;
	if (!tmp)
		return (NULL);
	if (flag && ft_check_dollar(tmp))
	{
		des = expand_variable(tmp, var);
		free(tmp);
		*res = NULL;
		if (!des)
			return (NULL);
	}
	else
		des = tmp;
	return (des);
}

static char	*get_all_data(char *str, t_list **lst, t_list *var, int flag)
{
	char	*input;
	char	*res;
	char	*des;

	while (1)
	{
		input = ft_get_line(str);
		if (!input)
			break ;
		res = ft_strjoin(input, "\n");
		des = switch_variable(&res, var, flag);
		free(input);
		input = NULL;
		if (!des)
			return (ft_listclear(lst), NULL);
		ft_listadd_back(lst, ft_listnew(des, -1));
	}
	res = ft_linkedlst_string(*lst);
	if (!res)
		res = ft_strdup("");
	ft_listclear(lst);
	return (res);
}

char	*get_heredoc_fd(char *str, t_list *var, int flag)
{
	char	*res;
	t_list	*lst;

	if (!str)
		return (NULL);
	lst = NULL;
	res = get_all_data(str, &lst, var, flag);
	if (!res)
		return (NULL);
	return (res);
}
