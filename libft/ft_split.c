/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtoky-fa <rtoky-fa@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 06:31:41 by rtoky-fa          #+#    #+#             */
/*   Updated: 2025/04/08 02:01:57 by rtoky-fa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *str, char c)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		while (*str == c)
			str++;
		while (*str != '\0' && *str != c)
		{
			str++;
			if (*str == c || *str == '\0')
				count++;
		}
	}
	return (count);
}

static int	count_letter(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	return (i);
}

static char	**free_tab(char **tab, int i)
{
	while (i-- > 0)
	{
		free(tab[i]);
	}
	free(tab);
	return (NULL);
}

static char	**fill_tab(char **result, const char *s, char c)
{
	int	i;
	int	len_letter;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			len_letter = count_letter(s, c);
			result[i] = ft_substr(s, 0, len_letter);
			if (!result[i])
				return (free_tab(result, i));
			i++;
			s += len_letter;
		}
	}
	result[i] = NULL;
	return (result);
}

char	**ft_split(const char *s, char c)
{
	int		len_word;
	char	**result;

	if (!s)
		return (NULL);
	len_word = count_words(s, c);
	result = (char **)malloc(sizeof(char *) * (len_word + 1));
	if (!result)
		return (NULL);
	return (fill_tab(result, s, c));
}
