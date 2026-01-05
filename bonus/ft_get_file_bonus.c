/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_file_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 23:00:25 by landriam          #+#    #+#             */
/*   Updated: 2025/12/30 16:15:12 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

char	*ft_get_file(int i)
{
	char	*res;
	char	*str;

	str = ft_itoa(i);
	if (!str)
		return (NULL);
	res = ft_strjoin("/tmp/minishell_", str);
	if (!res)
	{
		free(str);
		return (NULL);
	}
	free(str);
	return (res);
}
