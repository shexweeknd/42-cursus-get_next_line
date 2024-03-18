/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hramaros <hramaros@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:05:14 by hramaros          #+#    #+#             */
/*   Updated: 2024/03/18 03:19:14 by hramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*duplicate(const char *s)
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
	buffer->str = duplicate(content);
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

void	recurse_free(t_list *addr)
{
	free(addr->str);
	if (!addr->next)
	{
		free(addr);
		return ;
	}
	recurse_free(addr->next);
	addr->next = NULL;
	free(addr);
}
