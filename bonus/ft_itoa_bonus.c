/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:20:08 by landriam          #+#    #+#             */
/*   Updated: 2025/12/30 16:16:39 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	ft_str_size(int n)
{
	int	size;

	size = 0;
	if (n <= 0)
		size++;
	else
		n = -n;
	while (n < 0)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

static char	*ft_str_reverse(char *s)
{
	int		lenght;
	int		i;
	char	temp;

	lenght = 0;
	while (*(s + lenght))
		lenght++;
	i = 0;
	while (i < (lenght / 2))
	{
		temp = s[i];
		s[i] = s[lenght - (i + 1)];
		s[lenght - (i + 1)] = temp;
		i++;
	}
	return (s);
}

static char	*ft_get_number(int n, int sign)
{
	int		lenght;
	char	*str;

	lenght = ft_str_size(n);
	str = (char *)malloc((lenght + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	lenght = 0;
	if (!n)
		str[lenght++] = '0';
	if (n > 0)
		n = -n;
	while (n < 0)
	{
		str[lenght++] = (-(n % 10)) + '0';
		n = n / 10;
	}
	if (!sign)
		str[lenght++] = '-';
	str[lenght] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	int		sign;
	char	*str;

	sign = 0;
	if (n >= 0)
		sign++;
	str = ft_get_number(n, sign);
	if (str == NULL)
		return (NULL);
	ft_str_reverse(str);
	return (str);
}
