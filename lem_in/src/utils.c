/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 16:48:44 by apalanic          #+#    #+#             */
/*   Updated: 2017/03/28 16:48:46 by apalanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_bool		new_line_l(t_map *map)
{
	size_t	i;

	i = 0;
	while (i < map->rows)
	{
		if (map->arr[i][0] == 'L' || map->arr[i][0] == '\n' ||
			map->arr[i][0] == ' ' || map->arr[i][0] == '\t' ||
			map->arr[i][0] == '\v')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool		one_start_end(t_map *map)
{
	int		start;
	int		end;
	size_t	i;

	i = 0;
	start = 0;
	end = 0;
	while (i < map->rows)
	{
		if (!ft_strcmp("##start", map->arr[i]))
			start++;
		if (!ft_strcmp("##end", map->arr[i]))
			end++;
		i++;
	}
	return ((start == 1 && end == 1) ? (TRUE) : (FALSE));
}

t_bool		is_tube(char *str)
{
	int i;
	int space;
	int dash;

	space = 0;
	dash = 0;
	i = -1;
	if (str[0] == '#')
		return (FALSE);
	while (str[++i] != '\0')
	{
		if (str[i] == ' ')
			space++;
		else if (str[i] == '-')
			dash++;
	}
	if (space == 0 && dash > 0)
		return (TRUE);
	return (FALSE);
}

t_bool		is_com(char *str)
{
	return ((str[0] == '#') ? (TRUE) : (FALSE));
}

void		free_2darr(char ***arr)
{
	int		i;

	i = -1;
	if (*arr != NULL)
	{
		while ((*arr)[++i] != NULL)
		{
			free((*arr)[i]);
			(*arr)[i] = NULL;
		}
		free(*arr);
		(*arr) = NULL;
		arr = NULL;
	}
}
