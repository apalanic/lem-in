/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   way_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 16:48:57 by apalanic          #+#    #+#             */
/*   Updated: 2017/03/28 16:49:02 by apalanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		free_path(t_path **path)
{
	int		i;

	i = 0;
	if (path != NULL && *path != NULL)
	{
		while (i <= (*path)->connect_r)
		{
			if ((*path)->rooms[i] != NULL)
				free((*path)->rooms[i]);
			(*path)->rooms[i] = NULL;
			i++;
		}
		free((*path)->rooms);
		(*path)->rooms = NULL;
		free((*path));
		*path = NULL;
	}
}

t_path		*new_path(int rooms)
{
	t_path	*path;

	path = NULL;
	if ((path = (t_path *)malloc(sizeof(t_path))) == NULL)
		return (NULL);
	if ((path->rooms = (char **)malloc(sizeof(char *) * rooms)) == NULL)
		return (NULL);
	ft_bzero(path->rooms, sizeof(char *) * rooms);
	path->length = rooms;
	path->connect_r = -1;
	return (path);
}

void		free_path_last(t_path **path)
{
	if (path != NULL && *path != NULL)
	{
		if ((*path)->connect_r >= 0)
		{
			if ((*path)->rooms[(*path)->connect_r] != NULL)
				free((*path)->rooms[(*path)->connect_r]);
			(*path)->rooms[(*path)->connect_r] = NULL;
			(*path)->connect_r--;
		}
	}
}

void		add_new_path(t_farm *farm, t_path **path, char *name)
{
	if (path != NULL && *path == NULL)
	{
		*path = new_path(farm->ri);
		(*path)->connect_r++;
		(*path)->rooms[(*path)->connect_r] = ft_strdup(name);
	}
	else if (path != NULL)
	{
		(*path)->connect_r++;
		(*path)->rooms[(*path)->connect_r] = ft_strdup(name);
	}
}
