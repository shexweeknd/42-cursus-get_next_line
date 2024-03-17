/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hramaros <hramaros@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 07:23:17 by hramaros          #+#    #+#             */
/*   Updated: 2024/03/17 10:44:47 by hramaros         ###   ########.fr       */
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

static void	fullfill(t_list **lst_ptr, t_list *premier, char *buffer)
{
	int		i;
	int		j;
	t_list	*addr;
	char	*tmp;

	addr = premier;
	i = 0;
	while (premier && premier->str)
	{
		j = 0;
		while (premier->str[j] && premier->str[j] != '\n')
			buffer[i++] = premier->str[j++];
		if ((premier->str[j] == '\n') || (!premier->next))
			break ;
		premier = premier->next;
	}
	if (premier->str[j] == '\n' && (strlen(&premier->str[j]) > 1))
		tmp = create_tmp(premier, j, strlen(&premier->str[j + 1]));
	else
		tmp = "";
	recurse_free(addr);
	if (*tmp)
		addr = lstnew(tmp);
	else
		*lst_ptr = NULL;
}

char	*get_next_line(int fd)
{
	static t_list	**lst_ptr;
	t_list			*premier;
	char			*tmp;
	char			*buffer;

	if (!BUFFER_SIZE)
		return (NULL);
	tmp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp)
		return (NULL);
	tmp[BUFFER_SIZE] = '\0';
	if (!lst_ptr || *lst_ptr == NULL)
	{
		read(fd, tmp, BUFFER_SIZE);
		premier = lstnew(tmp);
		lst_ptr = &(premier);
	}
	while (!is_nl(tmp) && read(fd, tmp, BUFFER_SIZE) != 0)
		lstlast(*lst_ptr)->next = lstnew(tmp);
	free(tmp);
	buffer = (char *)malloc(sizeof(char) * (c_count(premier) + 2));
	buffer[c_count(premier)] = '\n';
	buffer[c_count(premier) + 1] = '\0';
	fullfill(lst_ptr, premier, buffer);
	return (buffer);
}
