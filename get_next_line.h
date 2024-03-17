/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hramaros <hramaros@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:05:21 by hramaros          #+#    #+#             */
/*   Updated: 2024/03/17 08:16:23 by hramaros         ###   ########.fr       */
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
	char			*str;
	struct s_list	*next;
}					t_list;

char				*get_next_line(int fd);

/*utils*/
t_list				*lstnew(void *content);
void				lstadd_back(t_list **lst, t_list *new);
void				recurse_free(t_list *addr);
t_list				*lstlast(t_list *lst);
char				*strdup(const char *s);
char				*create_tmp(t_list *lst, int j, size_t size);

#endif
