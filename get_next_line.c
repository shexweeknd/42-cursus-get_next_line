/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hramaros <hramaros@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 07:23:17 by hramaros          #+#    #+#             */
/*   Updated: 2024/03/16 13:56:11 by hramaros         ###   ########.fr       */
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

static void	fullfill(t_list *lst, char *buffer)
{
	int		i;
	int		j;
	t_list	*addr;
	char	*tmp;

	addr = lst;
	i = 0;
	while (lst && lst->str)
	{
		j = 0;
		while (lst->str[j] && lst->str[j] != '\n')
			buffer[i++] = lst->str[j++];
		if ((lst->str[j] == '\n') || (!lst->next))
			break ;
		lst = lst->next;
	}
	if (lst->str[j] == '\n')
	{
		tmp = (char *)malloc(sizeof(char) * (strlen(&lst->str[j + 1]) + 1));
		if (!tmp)
			return ;
		tmp[strlen(&(lst->str[j + 1]))] = '\0';
		i = 0;
		while (lst->str[j])
			tmp[i++] = lst->str[++j];
	}
	else 
		tmp = "";
	recurse_free(addr);
	if (*tmp)
		addr = lstnew(tmp);
}

char	*get_next_line(int fd)
{
	static t_list	*premier;
	char			*tmp;
	char			*buffer;

	tmp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp)
		return (NULL);
	tmp[BUFFER_SIZE] = '\0';
	if (!premier)
	{
		read(fd, tmp, BUFFER_SIZE);
		premier = lstnew(tmp);
	}
	while (!is_nl(tmp) && read(fd, tmp, BUFFER_SIZE) != 0)
		lstadd_back(&premier, lstnew(tmp));
	free(tmp);
	buffer = (char *)malloc(sizeof(char) * (c_count(premier) + 2));
	buffer[c_count(premier)] = '\n';
	buffer[c_count(premier) + 1] = '\0';
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