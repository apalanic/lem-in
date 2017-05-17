/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 13:42:28 by apalanic          #+#    #+#             */
/*   Updated: 2017/03/30 13:42:34 by apalanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		free_arr(t_map *map)
{
	map->rows = 0;
	map->size = 0;
	free(map->arr);
	free(map);
}

static void		realloc_map(t_map **src)
{
	t_map	*dst;
	size_t	i;

	i = 0;
	dst = new_map((*src)->size + 50);
	while (i < (*src)->rows)
	{
		dst->arr[i] = (*src)->arr[i];
		i++;
	}
	dst->rows = (*src)->rows;
	dst->rooms = (*src)->rooms;
	dst->size = (*src)->size + 50;
	free_arr(*src);
	*src = dst;
}

void			free_map(t_map *map)
{
	size_t	i;

	i = 0;
	while (i < map->rows)
		ft_strdel(&map->arr[i++]);
	free_arr(map);
}

t_map			*new_map(size_t size)
{
	t_map	*new;

	new = NULL;
	if ((new = (t_map *)malloc(sizeof(t_map))) == NULL)
		return (NULL);
	if ((new->arr = (char **)malloc(sizeof(char *) * size)) == NULL)
	{
		free(new);
		return (NULL);
	}
	ft_bzero(new->arr, sizeof(char *) * size);
	new->size = size;
	new->rows = 0;
	new->rooms = 0;
	new->is_start = FALSE;
	new->is_end = FALSE;
	return (new);
}

void			save_map(t_map **map)
{
	char	*tmp;

	while (get_next_line(0, &tmp) > 0)
	{
		if ((*map)->rows + 1 >= (*map)->size)
			realloc_map(map);
		(*map)->arr[(*map)->rows] = tmp;
		(*map)->rows++;
	}
	free(tmp);
}
