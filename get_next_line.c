/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hramaros <hramaros@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 07:23:17 by hramaros          #+#    #+#             */
/*   Updated: 2024/03/17 08:16:06 by hramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	c_count(t_list *lst)
{
	size_t	count;
	size_t	i;

	count = 0;
	while (lst)
	{
		i = 0;
		while (lst->str[i] && lst->str[i] != '\n')
			i++;
		count += i;
		lst = lst->next;
	}
	return (count);
}

static int	is_nl(char *str)
{
	while (*str)
		if (*str++ == '\n')
			return (1);
	return (0);
}

static size_t	strlen(const char *s)
{
	int	count;

	count = 0;
	while (s[count])
		count++;
	return (count);
}

static void	fullfill(t_list *lst, char *buffer)
{
	int		i;
	int		j;
	t_list	*addr;
	char	*tmp;

	addr = lst;
	i = 0;
	while (lst && lst->str)
	{
		j = 0;
		while (lst->str[j] && lst->str[j] != '\n')
			buffer[i++] = lst->str[j++];
		if ((lst->str[j] == '\n') || (!lst->next))
			break ;
		lst = lst->next;
	}
	if (lst->str[j] == '\n')
		tmp = create_tmp(lst, j, strlen(&lst->str[j + 1]));
	else
		tmp = "";
	recurse_free(addr);
	if (*tmp)
		addr = lstnew(tmp);
}

char	*get_next_line(int fd)
{
	static t_list	*premier;
	char			*tmp;
	char			*buffer;

	tmp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp)
		return (NULL);
	tmp[BUFFER_SIZE] = '\0';
	if (!premier)
	{
		read(fd, tmp, BUFFER_SIZE);
		premier = lstnew(tmp);
	}
	while (!is_nl(tmp) && read(fd, tmp, BUFFER_SIZE) != 0)
		lstlast(premier)->next = lstnew(tmp);
	free(tmp);
	buffer = (char *)malloc(sizeof(char) * (c_count(premier) + 2));
	buffer[c_count(premier)] = '\n';
	buffer[c_count(premier) + 1] = '\0';
	fullfill(premier, buffer);
	return (buffer);
}
