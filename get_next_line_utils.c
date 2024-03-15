/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hramaros <hramaros@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:05:14 by hramaros          #+#    #+#             */
/*   Updated: 2024/03/15 07:35:45 by hramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*lstnew(void *content)
{
	t_list	*buffer;

	buffer = (t_list *)malloc(sizeof(t_list));
	if (!buffer)
		return (NULL);
	buffer->content = content;
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
	(*del)((*lst)->content);
	free(*lst);
	*lst = NULL;
}