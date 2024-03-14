/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hramaros <hramaros@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 07:23:17 by hramaros          #+#    #+#             */
/*   Updated: 2024/03/14 16:47:59 by hramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	c_count(t_list **lst)
{
	size_t	count;

	count = 0;
	return (count);
}

static void	fullfill(t_list **list, char *buffer)
{
	int		i;
	t_list	**addr;
	char	*tmp;

	addr = list;
	// sauvegarde des contenu dans buffer
	i = 0;
	while (*list->next && *list->str)
	{
		while (*(*list->str + i) && *(*list->str + i) != '\n')
			*buffer++ = *(*list->str + i++);
		*list = *list->next;
	}
	tmp = *list->str;
	i = 0;
	// TODO modify last str and create a new str to stock as the first element of the list
	// free les elements de toute la liste
	while (*addr->next)
	{
		free(*addr->str);
		*addr = *addr->next;
	}
	// reinitialisation de la liste
	return ;
}

char	*get_next_line(int fd)
{
	static t_list	**premier;
	char			*tmp;
	char			*buffer;

	tmp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp)
		return (NULL);
	if (!premier)
	{
		read(fd, tmp, BUFFER_SIZE);
		lstadd_back(premier, lstnew(buffer));
	}
	while (!is_nl(tmp))
	{
		read(fd, tmp, BUFFER_SIZE);
		lstadd_back(premier, lstnew(buffer));
	}
	buffer = (char *)malloc(sizeof(char) * (c_count(premier)));
	// TODO
	fullfill(premier, buffer);
	return (buffer);
}

// algo, utiliser une liste chaine pour accelerer l'execution du programme

/*
// 1
	- creer une liste chainee statique qui s'etendra au fur et a mesure qu'on lit le fichier (la liste cree un nouvel element si il ne contient pas encore de premier element)

// 2 - verifier que chaque element de la liste ne contient pas de /n

// 3 - si l'element contient un
	/n alors on arrete d'ajouter un element suivant dans la liste

// 4
	- prendre la taille des caractere contenus dans tous les elements de la liste

// 5
	- malloc un buffer par la suite qui contiendra tous les caracteres contenus dans la liste

// 6
	- sauvegarde et modification de l'element de la liste qui contient le caractere '\n' puis free() de tous les elements de la liste et faire de l'element sauvegarde le premier element de la liste
*/