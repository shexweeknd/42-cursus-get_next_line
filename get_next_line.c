/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hramaros <hramaros@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 07:23:17 by hramaros          #+#    #+#             */
/*   Updated: 2024/03/14 08:07:46 by hramaros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	c_count(t_list **lst)
{
	size_t count;
	
	count = 0;
	return (count);
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
	//TODO 6
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