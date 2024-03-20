/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hramaros <hramaros@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 07:29:54 by hramaros          #+#    #+#             */
/*   Updated: 2024/03/20 07:31:36 by hramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

int	main(void)
{
	int			fd;
	char		*buffer;

	fd = open("file.txt", O_RDONLY);
	buffer = get_next_line(fd);
	printf("%s", buffer);
	buffer = get_next_line(fd);
	printf("%s", buffer);
	buffer = get_next_line(fd);
	printf("%s", buffer);
	buffer = get_next_line(fd);
	printf("%s", buffer);
	free(buffer);
	close(fd);
	return (0);
}
