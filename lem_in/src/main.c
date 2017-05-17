/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 16:48:14 by apalanic          #+#    #+#             */
/*   Updated: 2017/03/28 16:48:16 by apalanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	usage(void)
{
	ft_printf(BLUE"######------------------USAGE-------------------######\n");
	ft_printf("# ./lem-in [ENTER] OR ./lem-in < [FILE_NAME]\n");
	ft_printf("# number of ants [int > 0]\n");
	ft_printf("# the rooms [NAME intX intY] with one ##start & ##end");
	ft_printf("\n# the links [NAME1-NAME2]\n");
	ft_printf("######---------ROOMS NAME RESTRICTIONS----------######\n");
	ft_printf("## 1. NO 'L', '#', at the start of the room name.\n");
	ft_printf("## 2. NO '-' at the room name\n");
	ft_printf("######------------------------------------------######\n"EOC);
	exit(1);
}

static void	check(t_map *map)
{
	if (map->rows == 0 || !parser(map))
	{
		free_map(map);
		ft_putstr_fd(RED"Error: wrong map\n\n"EOC, 2);
		usage();
	}
}

static void	print_map(t_map *map)
{
	size_t	i;

	i = 0;
	while (i < map->rows)
		ft_printf("%s\n", map->arr[i++]);
	ft_printf("\n");
}

int			main(void)
{
	t_map	*map;
	t_ways	*best_ways;

	map = NULL;
	map = new_map(50);
	if (map == NULL)
	{
		ft_putstr_fd(RED"Error: could not allocate memory for map\n\n"EOC, 2);
		exit(1);
	}
	save_map(&map);
	check(map);
	if ((best_ways = get_best_way(map)) == NULL)
	{
		ft_putstr_fd(RED"Error: bad links beetwen rooms\n"EOC, 2);
		free_map(map);
		usage();
	}
	print_map(map);
	print_result(map, best_ways);
	free_map(map);
	free_ways(&best_ways);

	return (0);
}
