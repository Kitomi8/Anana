/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 09:34:24 by landriam          #+#    #+#             */
/*   Updated: 2025/12/30 16:19:41 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	lenght1;
	size_t	lenght2;

	lenght1 = 0;
	lenght2 = 0;
	if (!s1 || !s2)
		return (NULL);
	while (*(s1 + lenght1) || *(s2 + lenght2))
	{
		if (*(s1 + lenght1))
			lenght1++;
		if (*(s2 + lenght2))
			lenght2++;
	}
	join = (char *)malloc((lenght1 + lenght2 + 1) * sizeof(char));
	if (join == NULL)
		return (NULL);
	while (*s1)
		*join++ = *s1++;
	while (*s2)
		*join++ = *s2++;
	*join = '\0';
	return (join - (lenght1 + lenght2));
}
