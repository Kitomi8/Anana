/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 11:30:43 by landriam          #+#    #+#             */
/*   Updated: 2025/12/24 17:48:48 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_equal(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			len++;
			break ;
		}
		i++;
	}
	return (len);
}

static char	*get_name(char *str)
{
	int		i;
	int		len;
	char	*res;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] != '=')
			len++;
		else
			break ;
		i++;
	}
	res = ft_string_dup(str, len);
	if (!res)
		return (NULL);
	return (res);
}

static int	var_input(char *str, int check, t_list **var)
{
	char	*res;

	res = ft_strdup(str);
	if (!res)
		return (1);
	if (check)
		ft_listadd_back(var, ft_listnew(res, 2));
	else
		ft_listadd_back(var, ft_listnew(res, 1));
	return (0);
}

static int	check_var(char *str, char *name, int check, t_list *tmp)
{
	char	*src;

	while (tmp)
	{
		src = get_name(tmp->content);
		if (!src)
			return (-1);
		if (!ft_strcmp(src, name))
		{
			free(src);
			if (check)
			{
				src = ft_strdup(str);
				if (!src)
					return (-1);
				free(tmp->content);
				tmp->content = src;
				tmp->flag = 2;
			}
			return (0);
		}
		free(src);
		tmp = tmp->next;
	}
	return (1);
}

int	export_input(char *str, t_list **var)
{
	int		check;
	int		nbr;
	char	*name;
	t_list	*tmp;

	if (!var)
		return (1);
	check = check_equal(str);
	if (!*var)
		return (var_input(str, check, var));
	if (!check)
		name = ft_strdup(str);
	else
		name = get_name(str);
	if (!name)
		return (1);
	tmp = *var;
	nbr = check_var(str, name, check, tmp);
	if (nbr == -1)
		return (free(name), 1);
	if (!nbr)
		return (free(name), 0);
	free(name);
	return (var_input(str, check, var));
}
