/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hramaros <hramaros@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 07:23:17 by hramaros          #+#    #+#             */
/*   Updated: 2024/03/20 14:44:25 by hramaros         ###   ########.fr       */
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

static int	nl_number(char *str)
{
	int	occur;

	occur = 0;
	while (*str)
		if (*str++ == '\n')
			occur++;
	return (occur);
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
	char	*tmp;

	i = 0;
	while (premier && premier->str)
	{
		j = 0;
		while (premier->str[j])
		{
			buffer[i++] = premier->str[j];
			if (premier->str[j++] == '\n')
				break ;
		}
		if (!premier->next)
			break ;
		premier = premier->next;
	}
	tmp = create_tmp(premier, j, strlen(&premier->str[j]));
	recurse_free(lst_ptr);
	if (tmp != NULL)
	{
		*lst_ptr = lstnew(tmp);
		free(tmp);
	}
}

char	*get_next_line(int fd)
{
	static t_list	**lst_ptr;
	static t_list	*premier;
	char			*tmp;
	char			*buffer;

	if (!BUFFER_SIZE || (fd < 0))
		return (NULL);
	tmp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp)
		return (NULL);
	bezero(tmp, BUFFER_SIZE);
	if (!lst_ptr || *lst_ptr == NULL)
	{
		if (!read(fd, tmp, BUFFER_SIZE))
		{
			free(tmp);
			return (NULL);
		}
		premier = lstnew(tmp);
		lst_ptr = &(premier);
	}
	while (!nl_number((*lst_ptr)->str) && (nl_number(tmp) == 0) && bezero(tmp,
			BUFFER_SIZE) && read(fd, tmp, BUFFER_SIZE) != 0)
		lstlast(*lst_ptr)->next = lstnew(tmp);
	free(tmp);
	buffer = (char *)malloc(sizeof(char) * (c_count(premier) + 2));
	bezero(buffer, c_count(premier) + 1);
	fullfill(lst_ptr, premier, buffer);
	return (buffer);
}
