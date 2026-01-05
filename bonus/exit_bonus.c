/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:53:33 by landriam          #+#    #+#             */
/*   Updated: 2026/01/05 14:42:24 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	print_exit(t_command *cmd, t_node *node)
{
	int			len;
	t_command	*command;

	if (!node)
		return ;
	command = node->command;
	len = lenght_cmd(command);
	if (len == 1)
	{
		if (command->type == COMMAND_SIMPLE)
		{
			if (command == cmd)
			{
				ft_putstr_fd("exit\n", 2);
				return ;
			}
		}
	}
	print_exit(cmd, node->left);
	print_exit(cmd, node->right);
}

static int	check_arg(t_list *lst, t_store *store, t_store *all, int *nbr)
{
	int		check;
	char	*str;

	print_exit(store->cmd, all->node);
	if (lst->next)
	{
		str = lst->next->content;
		if (!*str)
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			return (2);
		}
	}
	check = check_numeric(lst, &store->var, nbr);
	return (check);
}

int	ft_exit(t_list **arg, t_store *store, t_store *all, int fds[2])
{
	int		status;
	int		nbr;
	int		check;
	t_list	*lst;

	nbr = 0;
	lst = *arg;
	check = check_arg(lst, store, all, &nbr);
	if (check != 1)
	{
		if (fds[0] > 2)
			close(fds[0]);
		if (fds[1] > 2)
			close(fds[1]);
		ft_listclear(arg);
		clear_all(all);
		if (check == 2)
			exit(2);
		status = (unsigned char)nbr;
		exit(status);
	}
	return (1);
}
