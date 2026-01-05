/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:40:56 by landriam          #+#    #+#             */
/*   Updated: 2025/12/30 16:19:28 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	len;

	len = 0;
	if (!s)
		return (NULL);
	while (*(s + len))
		len++;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (*s)
		*str++ = *s++;
	*str = '\0';
	return (str - len);
}

char	*ft_string_dup(const char *s, int lenght)
{
	int		i;
	int		len;
	char	*str;

	len = 0;
	if (!s)
		return (NULL);
	while (*(s + len))
		len++;
	if (len < lenght || lenght < 0)
		lenght = len;
	str = (char *)malloc((lenght + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] && i < lenght)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
