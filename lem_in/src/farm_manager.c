/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   farm_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 16:48:29 by apalanic          #+#    #+#             */
/*   Updated: 2017/03/28 16:48:32 by apalanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static t_bool	new_f_finish(t_map *map, t_farm *farm)
{
	int		i;

	i = -1;
	ft_bzero(farm->rooms, sizeof(t_room) * map->rooms + 1);
	while (++i < map->rooms)
	{
		farm->rooms[i].tube_count = 0;
		farm->rooms[i].is_end = FALSE;
		farm->rooms[i].is_start = FALSE;
		farm->rooms[i].is_empty = TRUE;
		farm->rooms[i].name = 0;
		if ((farm->rooms[i].mate = (t_room **)
				malloc(sizeof(t_room *) * map->rooms)) == NULL)
			return (FALSE);
		ft_bzero(farm->rooms[i].mate, sizeof(t_room *) * map->rooms);
	}
	farm->ant_count = ft_atoi(map->arr[0]);
	farm->ri = 0;
	return (TRUE);
}

t_farm			*new_farm(t_map *map)
{
	t_farm	*farm;

	farm = NULL;
	if ((farm = (t_farm *)malloc(sizeof(t_farm))) == NULL)
		return (NULL);
	if ((farm->rooms = (t_room *)malloc(sizeof(t_room) * map->rooms + 1)) ==
		NULL)
		return (NULL);
	if (!new_f_finish(map, farm))
		return (NULL);
	return (farm);
}

void			free_farm(t_farm *farm, t_map *map)
{
	int		i;

	i = -1;
	if (farm != NULL)
	{
		while (++i < map->rooms)
		{
			if (farm->rooms[i].mate != NULL)
				free(farm->rooms[i].mate);
			if (farm->rooms[i].name != NULL)
				free(farm->rooms[i].name);
		}
		if (farm->rooms != NULL)
			free(farm->rooms);
		free(farm);
	}
}

// char			*get_tube_name(char *str, t_map *map, int k, int j)
// {
// 	char	*name;
// 	char	n[120];
// 	size_t	len;

// 	len = 0;
// 	if ((name = ft_strnew(ft_strlen(str))) == NULL)
// 		return (NULL);
// 	while (++k && j < map->rooms)
// 	{
// 		if (map->arr[k][0] == '#')
// 			continue ;
// 		else if (++j && ft_bzero(n, sizeof(char) * 120))
// 		{
// 			ft_strncpy(n, map->arr[k], ft_strlen_chr(map->arr[k], ' '));
// 			len = ft_strlen(n);
// 			if (!ft_memcmp(n, str, len))
// 				j = map->rooms * 2;
// 		}
// 	}
// 	if (j == map->rooms * 2)
// 		return (ft_strcpy(name, n));
// 	else
// 		return (NULL);
// }

void			init_room(t_room *room, char *str)
{
	int		i;

	i = -1;
	room->name = ft_strnew(ft_strlen_chr(str, ' '));
	while (str[++i] != '\0' && str[i] != ' ')
	{
		room->name[i] = str[i];
		room->ant_index = 0;
		room->ant_count = 0;
	}
}
