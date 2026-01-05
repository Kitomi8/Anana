/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop_to_stack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:40:06 by landriam          #+#    #+#             */
/*   Updated: 2025/10/20 15:08:51 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*pop_terminal(t_stacktype *stack, int *top)
{
	t_stacktype	*head;

	head = stack + *top;
	*top = *top - 1;
	if (head->type == WORD)
		return (head->word);
	return (NULL);
}

t_redirect	*pop_redirect(t_stacktype *stack, int *top)
{
	t_stacktype	*head;

	head = stack + *top;
	*top = *top - 1;
	return (head->redirect);
}

t_command	*pop_command(t_stacktype *stack, int *top)
{
	t_stacktype	*head;

	head = stack + *top;
	*top = *top - 1;
	return (head->command);
}

t_node	*pop_node(t_stacktype *stack, int *top)
{
	t_stacktype	*head;

	head = stack + *top;
	*top = *top - 1;
	return (head->node);
}
