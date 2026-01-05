/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 10:32:01 by landriam          #+#    #+#             */
/*   Updated: 2025/12/30 16:26:30 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	ignore_signal(void)
{
	struct sigaction	sa1;
	struct sigaction	sa2;

	sa1.sa_handler = SIG_IGN;
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

int	default_signal(void)
{
	struct sigaction	sa1;
	struct sigaction	sa2;

	sa1.sa_handler = SIG_DFL;
	sigemptyset(&sa1.sa_mask);
	sa1.sa_flags = 0;
	if (sigaction(SIGINT, &sa1, NULL))
		return (ft_putstr_fd(strerror(errno), 2), 1);
	sa2.sa_handler = SIG_DFL;
	sigemptyset(&sa2.sa_mask);
	sa2.sa_flags = 0;
	if (sigaction(SIGQUIT, &sa2, NULL))
		return (ft_putstr_fd(strerror(errno), 2), 1);
	return (0);
}
