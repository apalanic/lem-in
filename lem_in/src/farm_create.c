/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   farm_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 16:48:29 by apalanic          #+#    #+#             */
/*   Updated: 2017/03/28 16:48:32 by apalanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_bool	find_nodes(t_farm *farm, char *tube1, char *tube2)
{
	t_room	*room1;
	t_room	*room2;
	t_room	*mate1;
	t_room	*mate2;

	room1 = NULL;
	room2 = NULL;
	mate1 = NULL;
	mate2 = NULL;
	room1 = find_room_by_name(farm, tube1);
	room2 = find_room_by_name(farm, tube2);
	mate1 = find_mate_by_name(room1, tube2);
	mate2 = find_mate_by_name(room2, tube1);
	if (mate1 != NULL && mate2 != NULL)
		return (TRUE);
	if (room1 != NULL && room2 != NULL)
	{
		room1->mate[room1->tube_count] = room2;
		room1->tube_count++;
		room2->mate[room2->tube_count] = room1;
		room2->tube_count++;
	}
	else
		return (FALSE);
	return (TRUE);
}

static int		create_tube(t_farm *farm, char *str)
{
	char	*tube1;
	char	*tube2;
	int		i;

	i = -1;
	if ((tube1 = ft_strnew(ft_strlen(str))) == NULL ||
		(tube2 = ft_strnew(ft_strlen(str))) == NULL)
		return (0);
	while (*str != '\0' && *str != '-' && (++i) >= 0)
	{
		tube1[i] = *str;
		str++;
	}
	str++;
	i = -1;
	while (*str != '\0' && *str != '-' && (++i) >= 0)
	{
		tube2[i] = *str;
		str++;
	}
	i = find_nodes(farm, tube1, tube2);
	free(tube1);
	free(tube2);
	return (i);
}

static t_bool	init_tubes(t_farm *farm, t_map *map, size_t i)
{
	while (i < map->rows)
	{
		if (!is_com(map->arr[i]))
			if (!create_tube(farm, map->arr[i]))
				return (FALSE);
		i++;
	}
	return (TRUE);
}

static void		init_rooms(t_map *map, size_t *i, t_farm *farm)
{
	char	**tmp;

	while (farm->ri < map->rooms)
	{
		tmp = ft_strsplit(map->arr[*i], ' ');
		if (!ft_strcmp("##start", tmp[0]) || !ft_strcmp("##end", tmp[0]))
		{
			init_room(farm->rooms + farm->ri, map->arr[++(*i)]);
			(!ft_strcmp("##end", map->arr[*i - 1])) ?
			(farm->rooms[farm->ri].is_end = TRUE) :
			(farm->rooms[farm->ri].is_start = TRUE);
			if (farm->rooms[farm->ri].is_start)
				farm->rooms[farm->ri].ant_index = farm->ant_count;
			(!ft_strcmp("##end", map->arr[*i - 1])) ?
			(farm->end = farm->rooms + farm->ri) :
			(farm->start = farm->rooms + farm->ri);
		}
		else if (!is_com(map->arr[*i]))
			init_room(farm->rooms + farm->ri, map->arr[*i]);
		(!is_com(map->arr[*i])) ? (farm->ri++) : 0;
		(*i)++;
		free_2darr(&tmp);
	}
}

t_farm			*create_farm(t_map *data)
{
	t_farm	*farm;
	size_t	i;

	i = 1;
	if ((farm = new_farm(data)) == NULL)
		return (NULL);
	farm->ant_count = ft_atoi(data->arr[0]);
	init_rooms(data, &i, farm);
	if (!init_tubes(farm, data, i))
	{
		free_farm(farm, data);
		return (NULL);
	}
	return (farm);
}
