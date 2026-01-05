/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_check_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 10:49:23 by landriam          #+#    #+#             */
/*   Updated: 2025/12/30 16:12:28 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	is_alpha(char c)
{
	if ((c >= 65 && c <= 90) || c == 95)
		return (0);
	if (c >= 97 && c <= 122)
		return (0);
	return (1);
}

static int	check_string(char *str)
{
	int	i;

	if (is_alpha(str[0]))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(str, 2);
		return (ft_putstr_fd("': not a valid identifier\n", 2), 1);
	}
	i = 1;
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
		if (is_alpha(str[i]))
		{
			if (!(str[i] >= 48 && str[i] <= 57))
			{
				ft_putstr_fd("minishell: export: `", 2);
				ft_putstr_fd(str, 2);
				return (ft_putstr_fd("': not a valid identifier\n", 2), 1);
			}
		}
		i++;
	}
	return (0);
}

int	export_check(t_list *arg, t_list **var)
{
	int		status;
	t_list	*tmp;

	if (!arg->next)
		return (0);
	tmp = arg->next;
	status = 0;
	while (tmp)
	{
		if (check_string(tmp->content))
		{
			tmp = tmp->next;
			status = 1;
			continue ;
		}
		if (export_input(tmp->content, var))
			return (1);
		tmp = tmp->next;
	}
	return (status);
}
