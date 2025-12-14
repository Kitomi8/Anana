/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtoky-fa <rtoky-fa@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:14:59 by rtoky-fa          #+#    #+#             */
/*   Updated: 2025/03/18 15:25:06 by rtoky-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (size > i && *dst)
	{
		dst++;
		i++;
	}
	if (i == size)
		return (i + ft_strlen(src));
	j = 0;
	while (src[j])
	{
		if (j < size - i - 1)
		{
			*dst = src[j];
			dst++;
		}
		j++;
	}
	*dst = '\0';
	return (i + j);
}
