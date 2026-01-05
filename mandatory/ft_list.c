/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: landriam <landriam@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 09:09:06 by landriam          #+#    #+#             */
/*   Updated: 2025/12/19 10:19:52 by landriam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_listnew(char *str, int fg)
{
	t_list	*lst;

	if (!str)
		return (NULL);
	lst = (t_list *)malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst->flag = fg;
	lst->content = str;
	lst->next = NULL;
	return (lst);
}

void	ft_listadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!lst || !new)
		return ;
	tmp = *lst;
	if (!tmp)
	{
		*lst = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	ft_linkedlen_content(t_list *head)
{
	int		len;
	t_list	*temp;

	len = 0;
	if (!head)
		return (-1);
	temp = head;
	while (temp)
	{
		if (temp->content)
			len += ft_strlen((const char *)temp->content);
		temp = temp->next;
	}
	return (len);
}

char	*ft_linkedlst_string(t_list *lst)
{
	char	*str;
	char	*src;
	int		index;
	int		len;
	t_list	*temp;

	src = NULL;
	len = ft_linkedlen_content(lst);
	if (!lst || len < 0)
		return (NULL);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	temp = lst;
	index = 0;
	while (temp && (index < len))
	{
		src = ((char *)temp->content);
		while (*src && (index < len))
			*(str + index++) = *src++;
		temp = temp->next;
	}
	*(str + index) = '\0';
	return (str);
}

void	ft_listclear(t_list **lst)
{
	t_list	*tmp;
	t_list	*cur;

	tmp = *lst;
	if (!lst || !tmp)
		return ;
	cur = NULL;
	while (tmp)
	{
		cur = tmp->next;
		free(tmp->content);
		free(tmp);
		tmp = NULL;
		tmp = cur;
	}
	*lst = NULL;
}
