/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:04:38 by landriam          #+#    #+#             */
/*   Updated: 2025/12/19 11:35:51 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exchange_list(t_list *head, char **arr, int len)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = head;
	while (tmp && i < len)
	{
		if (tmp->content)
		{
			arr[i++] = tmp->content;
			tmp->content = NULL;
		}
		tmp = tmp->next;
	}
	arr[i] = NULL;
}

char	**ft_array_list(t_list *head)
{
	int		len;
	char	**arr;

	if (!head)
		return (NULL);
	len = lenght_list(head);
	arr = (char **)malloc(sizeof(char *) * (len + 1));
	if (!arr)
		return (NULL);
	ft_exchange_list(head, arr, len);
	return (arr);
}

static int	ft_exchange_env(t_list *head, char **arr, int len, int fg)
{
	int		i;
	char	*str;
	t_list	*tmp;

	i = 0;
	tmp = head;
	while (tmp && i < len)
	{
		if (tmp->flag >= fg)
		{
			str = ft_strdup(tmp->content);
			if (!str)
			{
				arr[i] = NULL;
				return (1);
			}
			arr[i++] = str;
		}
		tmp = tmp->next;
	}
	arr[i] = NULL;
	return (0);
}

char	**ft_array_env(t_list *head, int fg)
{
	int		len;
	char	**arr;

	if (!head)
		return (NULL);
	len = lenght_env(head, fg);
	arr = (char **)malloc(sizeof(char *) * (len + 1));
	if (!arr)
		return (NULL);
	if (ft_exchange_env(head, arr, len, fg))
	{
		ft_clear_array(arr);
		return (NULL);
	}
	return (arr);
}
