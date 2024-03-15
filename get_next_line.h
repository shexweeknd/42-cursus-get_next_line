/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hramaros <hramaros@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:05:21 by hramaros          #+#    #+#             */
/*   Updated: 2024/03/15 07:49:24 by hramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	char *str;
	struct s_list *next;
}		t_list;

char	*get_next_line(int fd);

/*utils*/
t_list	*lstnew(void *content);
void	lstadd_front(t_list **lst, t_list *new);
void	lstclear(t_list **lst, void (*del)(void *));
t_list	*lstlast(t_list *lst);

#endif
