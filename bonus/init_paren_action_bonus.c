/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_paren_action_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 16:46:04 by landriam          #+#    #+#             */
/*   Updated: 2025/12/30 16:22:07 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	twenty_seventoeight_state(int state, t_nodetype terminal)
{
	if ((state == 27) && (terminal == PIPE))
		return (38);
	if ((state == 27) && ((terminal == AND) || (terminal == OR)))
		return (-2);
	if ((state == 27) && (terminal == CLOSE_PAREN))
		return (-2);
	if ((state == 28) && (terminal == WORD))
		return (39);
	if ((state == 28) && (terminal == LESS))
		return (31);
	if ((state == 28) && (terminal == DLESS))
		return (32);
	if ((state == 28) && (terminal == GREAT))
		return (33);
	if ((state == 28) && (terminal == DGREAT))
		return (34);
	if ((state == 28) && (terminal == PIPE || terminal == CLOSE_PAREN))
		return (-5);
	if ((state == 28) && (terminal == AND || terminal == OR))
		return (-5);
	return (0);
}

static int	second_action_state(int state, t_nodetype terminal)
{
	if ((state == 26) && (terminal == AND))
		return (36);
	if ((state == 26) && (terminal == OR))
		return (37);
	if ((state == 26) && (terminal == CLOSE_PAREN))
		return (35);
	if (!((terminal == OPEN_PAREN) || (terminal == END)))
	{
		if (state == 29)
			return (-7);
		if (state == 30)
			return (-8);
		if (state == 39)
			return (-9);
	}
	if (state == 40 && !(terminal == OPEN_PAREN))
		return (-10);
	if (state == 41 || state == 42 || state == 43 || state == 44)
	{
		if (!(terminal == OPEN_PAREN))
			return (-12);
	}
	return (0);
}

static int	thirty_onetoeight_state(int state, t_nodetype term)
{
	if ((state == 31) && (term == WORD))
		return (41);
	if ((state == 32) && (term == WORD))
		return (42);
	if ((state == 33) && (term == WORD))
		return (43);
	if ((state == 34) && (term == WORD))
		return (44);
	if (state == 35)
	{
		if (!(term == OPEN_PAREN || term == CLOSE_PAREN || term == WORD))
			return (-11);
	}
	if (((state == 36) || (state == 37) || (state == 38)) && (term == WORD))
		return (29);
	if (((state == 36) || (state == 37) || (state == 38)) && (term == LESS))
		return (31);
	if (((state == 36) || (state == 37) || (state == 38)) && (term == DLESS))
		return (32);
	if (((state == 36) || (state == 37) || (state == 38)) && (term == GREAT))
		return (33);
	if (((state == 36) || (state == 37) || (state == 38)) && (term == DGREAT))
		return (34);
	return (0);
}

static int	forty_seventoeight_state(int state, t_nodetype term)
{
	if (state == 47 && term == WORD)
		return (39);
	if (((state == 47) || (state == 48)) && (term == LESS))
		return (31);
	if (((state == 47) || (state == 48)) && (term == DLESS))
		return (32);
	if (((state == 47) || (state == 48)) && (term == GREAT))
		return (33);
	if (((state == 47) || (state == 48)) && (term == DGREAT))
		return (34);
	if ((state == 47) && (term == PIPE || term == AND || term == OR))
		return (-6);
	if ((state == 47) && (term == CLOSE_PAREN || term == END))
		return (-6);
	if ((state == 48) && (term == PIPE || term == AND || term == OR))
		return (-5);
	if ((state == 48) && (term == END))
		return (-5);
	return (0);
}

int	init_second_action(int state, t_nodetype term)
{
	if (((state == 45) || (state == 46)) && (term == PIPE))
		return (38);
	if ((state == 45) && ((term == AND) || (term == OR)))
		return (-3);
	if ((state == 45) && ((term == CLOSE_PAREN) || (term == END)))
		return (-3);
	if ((state == 46) && ((term == AND) || (term == OR)))
		return (-4);
	if ((state == 46) && ((term == CLOSE_PAREN) || (term == END)))
		return (-4);
	if (state == 27 || state == 28)
		return (twenty_seventoeight_state(state, term));
	if (state == 29 || state == 26)
		return (second_action_state(state, term));
	if (state == 30 || state == 39 || state == 40)
		return (second_action_state(state, term));
	if (state == 41 || state == 42 || state == 43 || state == 44)
		return (second_action_state(state, term));
	if (state == 31 || state == 32 || state == 33 || state == 34)
		return (thirty_onetoeight_state(state, term));
	if (state == 35 || state == 36 || state == 37 || state == 38)
		return (thirty_onetoeight_state(state, term));
	if (state == 47 || state == 48)
		return (forty_seventoeight_state(state, term));
	return (0);
}
