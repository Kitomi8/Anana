/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtoky-fa <rtoky-fa@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 01:27:14 by rtoky-fa          #+#    #+#             */
/*   Updated: 2025/03/24 15:25:20 by rtoky-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(long n)
{
	int	count;

	count = 0;
	if (n <= 0)
	{
		n = n * -1;
		count++;
	}
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		i;
	long	nb;
	char	*str;

	nb = n;
	i = count(n) - 1;
	str = (char *)ft_calloc((count(n) + 1), sizeof(char));
	if (!str)
		return (NULL);
	if (n < 0)
		nb *= -1;
	while (i >= 0)
	{
		str[i] = (nb % 10) + '0';
		nb = nb / 10;
		i--;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
