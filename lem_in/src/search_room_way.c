/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_room_way.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 16:48:29 by apalanic          #+#    #+#             */
/*   Updated: 2017/03/28 16:48:32 by apalanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	all_ways(t_farm *farm, t_room *r, t_ways **begin, t_path *path)
{
	int			i;
	t_room		*near;

	i = -1;
	if (r->is_end)
	{
		pb_new_way(begin, path);
		return ;
	}
	while (++i < r->tube_count)
	{
		near = r->mate[i];
		if (near->is_empty)
		{
			near->is_empty = FALSE;
			add_new_path(farm, &path, near->name);
			all_ways(farm, near, begin, path);
			free_path_last(&path);
			if (!near->is_start)
				near->is_empty = TRUE;
		}
	}
}

t_ways	*ways_founder(t_farm *farm)
{
	t_ways	*begin;
	t_path	*path;

	begin = NULL;
	path = NULL;
	add_new_path(farm, &path, farm->start->name);
	farm->start->is_empty = 0;
	all_ways(farm, farm->start, &begin, path);
	free_path(&path);
	return (begin);
}

t_room	*find_mate_by_name(t_room *room, char *name)
{
	int		i;

	i = -1;
	if (room == NULL || name == NULL)
		return (NULL);
	while (++i < room->tube_count)
	{
		if (!ft_strcmp(name, room->mate[i]->name))
			return (room->mate[i]);
	}
	return (NULL);
}

t_room	*find_room_by_name(t_farm *farm, char *name)
{
	int		i;

	i = -1;
	while (++i < farm->ri)
	{
		if (ft_strcmp(name, farm->rooms[i].name) == 0)
			return (&(farm->rooms[i]));
	}
	return (NULL);
}
