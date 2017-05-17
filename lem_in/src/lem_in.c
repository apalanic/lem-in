/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 16:48:14 by apalanic          #+#    #+#             */
/*   Updated: 2017/03/28 16:48:16 by apalanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		count_ways(t_farm *farm, t_ways *best_ways)
{
	int		steps;
	t_ways	*tmp;
	int		ants;

	steps = 1;
	ants = 0;
	while (ants < farm->ant_count)
	{
		ants = 0;
		tmp = best_ways;
		while (tmp != NULL)
		{
			ants += steps - tmp->way->connect_r + 2;
			if (ants >= farm->ant_count)
				return (steps - 1);
			tmp = tmp->next;
		}
		steps++;
	}
	return (INT_MAX);
}

static t_bool	way_is_present(t_ways **best_ways, t_path *path)
{
	int		i;
	t_ways	*current;

	current = *best_ways;
	if (current == NULL)
		return (FALSE);
	while (current != NULL)
	{
		i = -1;
		while (++i <= current->way->connect_r && i <= path->connect_r)
			if (ft_strcmp(current->way->rooms[i], path->rooms[i]))
				break ;
		if ((i == current->way->connect_r + 1) && (i == path->connect_r + 1))
			return (TRUE);
		current = current->next;
	}
	return (FALSE);
}

static t_bool	minw(t_ways *best_ways, t_ways *min_ways)
{
	int		best_i;
	int		min_i;
	t_ways	*best_curr;
	t_ways	*min_curr;

	best_i = 0;
	min_i = 0;
	best_curr = best_ways;
	min_curr = min_ways;
	if (min_ways == NULL)
		return (TRUE);
	while (best_curr != NULL && ++best_i)
		best_curr = best_curr->next;
	while (min_curr != NULL && ++min_i)
		min_curr = min_curr->next;
	if (best_i <= min_i)
		return (TRUE);
	return (FALSE);
}

static void		lem_in(t_farm *farm, t_ways **best_w, int *min_len,
	t_ways **min_w)
{
	t_ways	*begin;
	t_ways	*current;

	begin = ways_founder(farm);
	current = begin;
	while (current != NULL)
	{
		if (!way_is_present(best_w, current->way))
		{
			pb_new_way(best_w, current->way);
			if ((*min_len > count_ways(farm, *best_w)) ||
			(*min_len == count_ways(farm, *best_w) && minw(*best_w, *min_w)))
			{
				*min_len = count_ways(farm, *best_w);
				waycpy(min_w, best_w);
			}
			walk_by_way(farm, current->way);
			lem_in(farm, best_w, min_len, min_w);
			unwalk_way(farm, current->way);
			free_last_way(best_w);
		}
		current = current->next;
	}
	free_ways(&begin);
}

t_ways			*get_best_way(t_map *map)
{
	t_ways	*best_ways;
	t_ways	*min_ways;
	t_farm	*farm;
	int		min_length;

	min_length = INT_MAX;
	best_ways = NULL;
	min_ways = NULL;
	farm = create_farm(map);
	lem_in(farm, &best_ways, &min_length, &min_ways);
	free_farm(farm, map);
	free_ways(&best_ways);
	return (min_ways);
}
