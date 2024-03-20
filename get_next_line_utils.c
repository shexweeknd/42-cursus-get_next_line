/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hramaros <hramaros@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:05:14 by hramaros          #+#    #+#             */
/*   Updated: 2024/03/20 07:28:43 by hramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	bezero(char *str, size_t size)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (i <= size)
		str[i++] = '\0';
	return (1);
}

t_list	*lstnew(void *content)
{
	t_list	*buffer;
	int		size;

	buffer = (t_list *)malloc(sizeof(t_list));
	if (!buffer)
		return (NULL);
	size = 0;
	while (((char *)content)[size])
		size++;
	buffer->str = (char *)malloc(sizeof(char) * (size + 1));
	if (!buffer->str)
		return (NULL);
	size = 0;
	while (((char *)content)[size])
	{
		buffer->str[size] = ((char *)content)[size];
		size++;
	}
	buffer->str[size] = '\0';
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

char	*create_tmp(t_list *lst, int j, size_t size)
{
	char	*tmp;
	int		i;

	tmp = (char *)malloc(sizeof(char) * (size + 1));
	if (!tmp)
		return (NULL);
	tmp[size] = '\0';
	i = 0;
	while (lst->str[j])
		tmp[i++] = lst->str[j++];
	return (tmp);
}

void	recurse_free(t_list **lst_ptr)
{
	free((*lst_ptr)->str);
	(*lst_ptr)->str = NULL;
	if (!(*lst_ptr)->next)
	{
		free(*lst_ptr);
		*lst_ptr = NULL;
		return ;
	}
	recurse_free(&(*lst_ptr)->next);
	(*lst_ptr)->next = NULL;
	free(*lst_ptr);
	*lst_ptr = NULL;
}
