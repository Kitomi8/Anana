/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtoky-fa <rtoky-fa@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 09:14:34 by rtoky-fa          #+#    #+#             */
/*   Updated: 2025/12/24 16:27:17 by rtoky-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clean_exit(t_env *env, char **args, int code)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->value);
		free(env->key);
		free(env);
		env = tmp;
	}
	if (args)
		free_tab(args);
	exit(code);
}

static int	is_numeric(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	print_numeric_error(char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
}

int	ft_exit(char **args, t_env **env)
{
	int	status;

	ft_putendl_fd("exit", 1);
	if (!args[1])
		clean_exit(*env, args, g_signal);
	if (!is_numeric(args[1]))
	{
		print_numeric_error(args[1]);
		clean_exit(*env, args, 2);
	}
	if (args[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	status = ft_atoi(args[1]);
	clean_exit(*env, args, (unsigned char)status);
	return (0);
}
