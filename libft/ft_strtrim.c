/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtoky-fa <rtoky-fa@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:04:24 by rtoky-fa          #+#    #+#             */
/*   Updated: 2025/03/24 17:38:48 by rtoky-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static void	cut(char *result, const char *s1, size_t start, size_t end)
{
	int	i;

	i = 0;
	while (start < end)
	{
		result[i] = s1[start];
		i++;
		start++;
	}
	result[i] = '\0';
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	start;
	size_t	end;
	char	*result;

	if (*set == 0)
		return (ft_strdup(s1));
	start = 0;
	while (s1[start] && (check(s1[start], set) == 1))
		start++;
	end = ft_strlen(s1);
	while (end > start && (end != 0) && (check((s1[end - 1]), set) == 1))
	{
		end--;
		if (start >= end)
			return (ft_strdup(" "));
	}
	result = malloc(sizeof(char) * (end - start + 1));
	if (!result)
		return (NULL);
	cut(result, s1, start, end);
	return (result);
}
