/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walking_ways.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 16:48:57 by apalanic          #+#    #+#             */
/*   Updated: 2017/03/28 16:49:02 by apalanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			walk_by_way(t_farm *farm, t_path *path)
{
	int			i;
	int			j;

	i = 0;
	while (++i < path->connect_r)
	{
		j = -1;
		while (++j < farm->ri)
		{
			if (!farm->rooms[j].is_start &&
				!ft_strcmp(farm->rooms[j].name, path->rooms[i]))
				farm->rooms[j].is_empty = FALSE;
		}
	}
	farm->start->is_empty = FALSE;
	farm->end->is_empty = TRUE;
}

void			unwalk_way(t_farm *farm, t_path *path)
{
	int			i;
	int			j;

	i = 0;
	while (++i < path->connect_r)
	{
		j = -1;
		while (++j < farm->ri)
		{
			if (!farm->rooms[j].is_start &&
				!ft_strcmp(farm->rooms[j].name, path->rooms[i]))
				farm->rooms[j].is_empty = TRUE;
		}
	}
	farm->start->is_empty = FALSE;
	farm->end->is_empty = TRUE;
}
