/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hramaros <hramaros@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 14:24:42 by hramaros          #+#    #+#             */
/*   Updated: 2024/10/24 14:10:56 by hramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_sup_strchr(char *str, char c)
{
	int	index;

	if (!str)
		return (0);
	index = 0;
	while (str[index])
		if (str[index++] == c)
			return (1);
	return (0);
}

static char	*ft_sup_strjoin(char *remains, char *buffer)
{
	char	*result;
	int		i;
	int		j;

	if (!remains && !buffer)
		return (NULL);
	result = malloc(sizeof(char) * (ft_strlen(remains) + ft_strlen(buffer)
				+ 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	if (remains)
	{
		while (remains[i])
			result[j++] = remains[i++];
	}
	i = 0;
	while (buffer[i])
		result[j++] = buffer[i++];
	result[ft_strlen(remains) + ft_strlen(buffer)] = '\0';
	return (free(remains), result);
}

static char	*push_line(char *buffer)
{
	char	*result;
	int		i;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	result = malloc(sizeof(char) * (i + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		result[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		return (result[i] = '\n', result[i + 1] = '\0', result);
	return (result[i] = '\0', result);
}

static char	*get_remains(char *remains)
{
	int		i;
	int		j;
	char	*result;

	if (!remains)
		return (NULL);
	i = 0;
	while (remains[i] && remains[i] != '\n')
		i++;
	if (remains[i] == '\0')
		return (free(remains), NULL);
	result = malloc(sizeof(char) * (ft_strlen(&remains[i]) + 1));
	if (!result)
		return (NULL);
	i++;
	j = 0;
	while (remains[i])
		result[j++] = remains[i++];
	return (result[j] = '\0', free(remains), result);
}

char	*get_next_line(int fd)
{
	static char	*remains;
	char		*result;
	char		buffer[BUFFER_SIZE + 1];
	int			count;

	if (fd < 0 || !BUFFER_SIZE)
		return (NULL);
	count = 1;
	buffer[0] = '\0';
	while (!ft_sup_strchr(buffer, '\n') && count)
	{
		count = read(fd, buffer, BUFFER_SIZE);
		buffer[count] = '\0';
		remains = ft_sup_strjoin(remains, buffer);
	}
	result = push_line(remains);
	remains = get_remains(remains);
	if (result[0] == '\0')
		return (free(result), NULL);
	return (result);
}
