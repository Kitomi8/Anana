/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 11:51:11 by landriam          #+#    #+#             */
/*   Updated: 2025/11/20 14:53:54 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_words_count(char const *s, char c)
{
	int	number;

	number = 0;
	while (*s)
	{
		if (*s != c)
			number++;
		while (*s != c && *s)
			s++;
		if (*s)
			s++;
	}
	return (number);
}

static int	*ft_letters_count(const char *s, char c)
{
	int	*tab;
	int	lenght;
	int	number;

	lenght = ft_words_count(s, c);
	tab = (int *)malloc((lenght + 1) * sizeof(int));
	if (tab == NULL)
		return (NULL);
	while (*s)
	{
		number = 0;
		while (*s != c && *s)
		{
			number++;
			s++;
		}
		if (number)
			*tab++ = number;
		if (*s)
			s++;
	}
	*tab = 0;
	return (tab - lenght);
}

char	**ft_split(char const *s, char c)
{
	int		words_number;
	int		*tab;
	int		i;
	int		j;
	char	**array;

	if (!s)
		return (NULL);
	words_number = ft_words_count(s, c);
	tab = ft_letters_count(s, c);
	array = (char **)malloc((words_number + 1) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	i = 0;
	while (i < words_number)
	{
		array[i] = (char *)malloc((tab[i] + 1) * sizeof(char));
		while (*s == c)
			s++;
		j = 0;
		while (*s != c && *s)
			*(array[i] + j++) = *s++;
		*(array[i++] + j) = '\0';
	}
	return (free(tab), array[i] = NULL, array);
}
