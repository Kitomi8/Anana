/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_goto.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:57:43 by landriam          #+#    #+#             */
/*   Updated: 2025/12/24 17:40:54 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	three_first_state(int state, t_nodetype terminal)
{
	if ((state == 0) && (terminal == WORD))
		return (5);
	if ((state == 0) && (terminal == LESS))
		return (8);
	if ((state == 0) && (terminal == DLESS))
		return (9);
	if ((state == 0) && (terminal == GREAT))
		return (10);
	if ((state == 0) && (terminal == DGREAT))
		return (11);
	if ((state == 0) && (terminal == OPEN_PAREN))
		return (7);
	if ((state == 1) && (terminal == END))
		return (999);
	if ((state == 2) && (terminal == AND))
		return (12);
	if ((state == 2) && (terminal == OR))
		return (13);
	if ((state == 2) && (terminal == END))
		return (999);
	return (0);
}

int	action_state(int state, t_nodetype terminal)
{
	if (!((terminal == OPEN_PAREN) || (terminal == CLOSE_PAREN)))
	{
		if (state == 5)
			return (-7);
		if (state == 6)
			return (-8);
	}
	if (state == 15)
	{
		if (!((terminal == OPEN_PAREN) || (terminal == CLOSE_PAREN)))
			return (-9);
	}
	if (state == 16)
	{
		if (!((terminal == OPEN_PAREN) || (terminal == CLOSE_PAREN)))
			return (-10);
	}
	if ((state == 18) || (state == 19) || (state == 20) || (state == 21))
	{
		if (!((terminal == OPEN_PAREN) || (terminal == CLOSE_PAREN)))
			return (-12);
	}
	return (0);
}

static int	zero_state(int state, t_nodetype non_term)
{
	if ((state == 0) && (non_term == REDIRECT))
		return (6);
	if (state == 0)
	{
		if (non_term == COMMAND_SIMPLE)
			return (4);
		if (non_term == COMMAND_COMPOUND)
			return (48);
	}
	if ((state == 0) && (non_term == PIPELINE))
		return (3);
	if (state == 0)
	{
		if (non_term == SEQUENCE)
			return (2);
		if (non_term == AND || non_term == OR)
			return (2);
	}
	if ((state == 0) && (non_term == START))
		return (1);
	return (0);
}

static int	middle_state(int state, t_nodetype nterm)
{
	if (state == 7)
	{
		if (nterm == REDIRECT)
			return (30);
		if (nterm == COMMAND_SIMPLE || nterm == COMMAND_COMPOUND)
			return (28);
		if (nterm == PIPELINE)
			return (27);
		if (nterm == SEQUENCE || nterm == AND || nterm == OR)
			return (26);
	}
	if (state == 14 && (nterm == COMMAND_SIMPLE || nterm == COMMAND_COMPOUND))
		return (24);
	if ((state == 12 || state == 13 || state == 14) && (nterm == REDIRECT))
		return (6);
	if (((state == 12) || (state == 13)) && (nterm == COMMAND_SIMPLE))
		return (4);
	if (((state == 12) || (state == 13)) && (nterm == COMMAND_COMPOUND))
		return (4);
	if ((state == 12) && (nterm == PIPELINE))
		return (22);
	if ((state == 13) && (nterm == PIPELINE))
		return (23);
	return (0);
}

int	init_goto(int state, t_nodetype nterm)
{
	if (state == 0)
		return (zero_state(state, nterm));
	if (state == 7)
		return (middle_state(state, nterm));
	if ((state == 4 || state == 24) && (nterm == REDIRECT))
		return (16);
	if (state == 12 || state == 13 || state == 14)
		return (middle_state(state, nterm));
	if ((state == 28 || state == 47 || state == 48) && (nterm == REDIRECT))
		return (40);
	if (((state == 36) || (state == 37)) && (nterm == REDIRECT))
		return (30);
	if (((state == 36) || (state == 37)) && (nterm == COMMAND_SIMPLE))
		return (28);
	if (state == 36 && nterm == PIPELINE)
		return (45);
	if (state == 37 && nterm == PIPELINE)
		return (46);
	if (state == 38)
	{
		if (nterm == COMMAND_SIMPLE || nterm == COMMAND_COMPOUND)
			return (47);
	}
	return (0);
}
