/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtoky-fa <rtoky-fa@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 16:02:33 by rtoky-fa          #+#    #+#             */
/*   Updated: 2025/03/18 15:43:09 by rtoky-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*stock;
	size_t	size_t_max;

	size_t_max = -1;
	if (size != 0 && (nmemb) > (size_t_max / size))
		return (NULL);
	stock = malloc(nmemb * size);
	if (stock == NULL)
		return (NULL);
	ft_bzero(stock, (nmemb * size));
	return (stock);
}
