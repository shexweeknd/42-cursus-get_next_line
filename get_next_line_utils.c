/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hramaros <hramaros@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:05:14 by hramaros          #+#    #+#             */
/*   Updated: 2024/03/16 08:06:55 by hramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*strdup(const char *s)
{
	char	*ret;
	int		size;

	size = 0;
	while (s[size])
		size++;
	ret = (char *)malloc(sizeof(char) * (size + 1));
	if (!ret)
		return (0);
	size = 0;
	while (s[size])
	{
		*(ret + size) = s[size];
		size++;
	}
	ret[size] = '\0';
	return (ret);
}

t_list	*lstnew(void *content)
{
	t_list	*buffer;

	buffer = (t_list *)malloc(sizeof(t_list));
	if (!buffer)
		return (NULL);
	buffer->str = strdup(content);
	buffer->next = NULL;
	return (buffer);
}

t_list	*lstlast(t_list *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
	return (lst);
}

void	lstadd_back(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	lstlast(*lst)->next = new;
}

void	lstclear(t_list **lst, void (*del)(void *))
{
	if (*lst == NULL)
		return ;
	lstclear(&(*lst)->next, del);
	(*del)((*lst)->str);
	free(*lst);
	*lst = NULL;
}