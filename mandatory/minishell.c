/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 17:00:24 by landriam          #+#    #+#             */
/*   Updated: 2025/12/26 16:42:07 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig = 0;

static void	close_fd(t_here_doc **doc)
{
	t_here_doc	*tmp;

	if (!doc || !*doc)
		return ;
	tmp = *doc;
	while (tmp)
	{
		if (tmp->source)
		{
			close(tmp->fd);
			unlink(tmp->source);
		}
		tmp = tmp->next;
	}
}

static void	clear_store(t_store *store)
{
	close_fd(&store->doc);
	clear_node(&store->node);
	clear_here_doc(&store->doc);
}

static int	space_remove(char *input)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (input[i])
	{
		if (input[i] == ' ' || input[i] == 9 || input[i] == 10)
			len++ ;
		else
			break ;
		i++;
	}
	return (len);
}

static int	get_input(t_store *store)
{
	int		i;
	char	*input;

	input = NULL;
	if (signal_reading())
		return (free(input), exit_status(store->var, 1), 1);
	input = readline("minishell> ");
	if (g_sig == 2)
	{
		exit_status(store->var, 130);
		g_sig = 0;
	}
	if (ignore_signal())
		return (free(input), exit_status(store->var, 1), 1);
	if (!input)
		return (ft_putstr_fd("exit\n", 2), -1);
	add_history(input);
	i = space_remove(input);
	if (input[i] == '\0')
		return (free(input), exit_status(store->var, 0), 1);
	store->node = parse_input(input + i, &store->doc, store->var);
	if (!store->node)
		return (clear_here_doc(&store->doc), free(input), 1);
	return (free(input), 0);
}

int	main(int argc, char *argv[], char *envp[])
{
	int			nbr;
	int			status;
	t_store		store;

	(void)argc;
	(void)argv;
	store = (t_store){NULL, NULL, NULL, NULL};
	store.var = get_env(envp);
	input_variable(&store.var);
	while (1)
	{
		nbr = get_input(&store);
		if (nbr == 1)
			continue ;
		if (nbr == -1)
			break ;
		status = execution(&store, &store);
		if (status == 131)
			write(1, "Quit (core dumped)\n", 19);
		if (status == 130)
			write(1, "\n", 1);
		clear_store(&store);
	}
	return (ft_listclear(&store.var), 0);
}
