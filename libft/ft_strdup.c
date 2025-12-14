/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtoky-fa <rtoky-fa@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 02:28:36 by rtoky-fa          #+#    #+#             */
/*   Updated: 2025/03/24 15:17:37 by rtoky-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*dest;

	len = ft_strlen(s) + 1;
	dest = (char *)malloc(sizeof(char) * len);
	if (dest == NULL)
		return (NULL);
	len = 0;
	while (s[len])
	{
		dest[len] = s[len];
		len++;
	}
	dest[len] = '\0';
	return (dest);
}
