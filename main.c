/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hramaros <hramaros@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 07:29:54 by hramaros          #+#    #+#             */
/*   Updated: 2024/03/20 08:25:43 by hramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

int	main(void)
{
	char	*line;
	int		fd;
	int		i;

	fd = open("file.txt", O_RDONLY);
	if (!fd)
		return (1);
	i = 0;
	while (i++ < 10000)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		else
			printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
