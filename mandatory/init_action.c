/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_action.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 15:38:06 by landriam          #+#    #+#             */
/*   Updated: 2025/12/26 15:11:59 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	third_forth_state(int state, t_nodetype terminal)
{
	if ((state == 3) && (terminal == PIPE))
		return (14);
	if ((state == 3) && ((terminal == AND) || (terminal == OR)))
		return (-2);
	if ((state == 3) && (terminal == END))
		return (999);
	if ((state == 4) && (terminal == WORD))
		return (15);
	if ((state == 4) && (terminal == LESS))
		return (8);
	if ((state == 4) && (terminal == DLESS))
		return (9);
	if ((state == 4) && (terminal == GREAT))
		return (10);
	if ((state == 4) && (terminal == DGREAT))
		return (11);
	if ((state == 4) && ((terminal == AND) || (terminal == OR)))
		return (-5);
	if ((state == 4) && ((terminal == PIPE) || (terminal == END)))
		return (-5);
	return (0);
}

static int	seven_to_eleven_state(int state, t_nodetype terminal)
{
	if ((state == 7) && (terminal == WORD))
		return (29);
	if ((state == 7) && (terminal == LESS))
		return (31);
	if ((state == 7) && (terminal == DLESS))
		return (32);
	if ((state == 7) && (terminal == GREAT))
		return (33);
	if ((state == 7) && (terminal == DGREAT))
		return (34);
	if ((state == 8) && (terminal == WORD))
		return (18);
	if ((state == 9) && (terminal == WORD))
		return (19);
	if ((state == 10) && (terminal == WORD))
		return (20);
	if ((state == 11) && (terminal == WORD))
		return (21);
	return (0);
}

static int	twelve_to_fourteen_state(int state, t_nodetype terminal)
{
	if ((state == 12 || state == 13 || state == 14) && (terminal == WORD))
		return (5);
	if ((state == 12 || state == 13 || state == 14) && (terminal == LESS))
		return (8);
	if ((state == 12 || state == 13 || state == 14) && (terminal == DLESS))
		return (9);
	if ((state == 12 || state == 13 || state == 14) && (terminal == GREAT))
		return (10);
	if ((state == 12 || state == 13 || state == 14) && (terminal == DGREAT))
		return (11);
	if ((state == 12 || state == 13 || state == 14))
	{
		if (terminal == OPEN_PAREN)
			return (7);
	}
	if ((state == 12 || state == 13 || state == 14) && (terminal == END))
		return (4242);
	return (0);
}

static int	twenty_twotofour_state(int state, t_nodetype terminal)
{
	if ((state == 22 || state == 23) && (terminal == PIPE))
		return (14);
	if (terminal == AND || terminal == OR || terminal == END)
	{
		if (state == 22)
			return (-3);
		if (state == 23)
			return (-4);
	}
	if ((state == 24) && (terminal == WORD))
		return (15);
	if ((state == 24) && (terminal == LESS))
		return (8);
	if ((state == 24) && (terminal == DLESS))
		return (9);
	if ((state == 24) && (terminal == GREAT))
		return (10);
	if ((state == 24) && (terminal == DGREAT))
		return (11);
	if ((state == 24) && ((terminal == PIPE) || (terminal == END)))
		return (-6);
	if ((state == 24) && ((terminal == AND) || (terminal == OR)))
		return (-6);
	return (0);
}

int	init_action(int state, t_nodetype terminal)
{
	if (state == 0 || state == 1 || state == 2)
		return (three_first_state(state, terminal));
	if ((state == 3) || (state == 4))
		return (third_forth_state(state, terminal));
	if ((state == 5) || (state == 6))
		return (action_state(state, terminal));
	if ((state == 7) || (state == 8) || (state == 9))
		return (seven_to_eleven_state(state, terminal));
	if ((state == 10) || (state == 11))
		return (seven_to_eleven_state(state, terminal));
	if ((state == 12) || (state == 13) || (state == 14))
		return (twelve_to_fourteen_state(state, terminal));
	if ((state == 15) || (state == 16) || (state == 18))
		return (action_state(state, terminal));
	if ((state == 19) || (state == 20) || (state == 21))
		return (action_state(state, terminal));
	if ((state == 22) || (state == 23) || (state == 24))
		return (twenty_twotofour_state(state, terminal));
	return (init_second_action(state, terminal));
}
