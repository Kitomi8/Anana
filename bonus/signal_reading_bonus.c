/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_reading_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 15:19:42 by landriam          #+#    #+#             */
/*   Updated: 2025/12/30 16:26:45 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	handler(int signum)
{
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_sig = 2;
}

int	signal_reading(void)
{
	struct sigaction	sa1;
	struct sigaction	sa2;

	sa1.sa_handler = handler;
	sigemptyset(&sa1.sa_mask);
	sa1.sa_flags = 0;
	if (sigaction(SIGINT, &sa1, NULL))
		return (ft_putstr_fd(strerror(errno), 2), 1);
	sa2.sa_handler = SIG_IGN;
	sigemptyset(&sa2.sa_mask);
	sa2.sa_flags = 0;
	if (sigaction(SIGQUIT, &sa2, NULL))
		return (ft_putstr_fd(strerror(errno), 2), 1);
	return (0);
}

int	signal_heredoc(void)
{
	struct sigaction	sa1;
	struct sigaction	sa2;

	sa1.sa_handler = SIG_DFL;
	sigemptyset(&sa1.sa_mask);
	sa1.sa_flags = 0;
	if (sigaction(SIGINT, &sa1, NULL))
		return (ft_putstr_fd(strerror(errno), 2), 1);
	sa2.sa_handler = SIG_IGN;
	sigemptyset(&sa2.sa_mask);
	sa2.sa_flags = 0;
	if (sigaction(SIGQUIT, &sa2, NULL))
		return (ft_putstr_fd(strerror(errno), 2), 1);
	return (0);
}
