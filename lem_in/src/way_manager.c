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

static t_ways	*new_list(t_path *node)
{
	t_ways	*new;
	t_path	*way;
	int		i;

	i = -1;
	if ((new = (t_ways *)malloc(sizeof(t_ways))) == NULL)
		return (NULL);
	if ((new->way = new_path(node->length)) == NULL)
	{
		free(new);
		return (NULL);
	}
	way = new->way;
	while (++i <= node->connect_r)
		way->rooms[i] = ft_strdup(node->rooms[i]);
	way->connect_r = node->connect_r;
	way->length = node->length;
	new->next = NULL;
	return (new);
}

void			free_last_way(t_ways **way)
{
	t_ways	**curr;

	if (way != NULL && *way != NULL)
	{
		curr = way;
		while ((*curr)->next != NULL)
			curr = &(*curr)->next;
		free_path(&(*curr)->way);
		free(*curr);
		*curr = NULL;
	}
}

void			free_ways(t_ways **way)
{
	while (*way != NULL)
		free_last_way(way);
}

void			pb_new_way(t_ways **begin, t_path *src)
{
	t_ways	*current;

	if (!*begin)
	{
		*begin = new_list(src);
		(*begin)->ants_in = 0;
	}
	else
	{
		current = *begin;
		while (current->next)
			current = current->next;
		current->next = new_list(src);
		current->ants_in = 0;
	}
}

void			waycpy(t_ways **dst, t_ways **src)
{
	t_ways	*begin;

	begin = *src;
	free_ways(dst);
	while (begin != NULL)
	{
		pb_new_way(dst, begin->way);
		begin = begin->next;
	}
}
