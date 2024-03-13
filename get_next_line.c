/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hramaros <hramaros@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 07:23:17 by hramaros          #+#    #+#             */
/*   Updated: 2024/03/13 08:22:38 by hramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	read_char(int fd)
{
	char	c;

	read(fd, &c, 1);
	return (c);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	int			i;
	static int	offset = 0;

	// iterer jusqu'a trouver un '\n'
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	buffer[BUFFER_SIZE] = '\0';
	i = 0;
	while ((i < BUFFER_SIZE) && buffer[i] != '\n')
		buffer[i++] = read_char(fd);
	// ajoute une fonction qui skip le reste indesirable de la ligne et met le curseur 'offset' a la nouvelle ligne
	buffer[i] = '\n';
	return (buffer);
}
