/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_like_to_move_it.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 16:48:29 by apalanic          #+#    #+#             */
/*   Updated: 2017/03/28 16:48:32 by apalanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	move_r2r(t_room *curr, t_room *next)
{
	next->ant_index = curr->ant_index;
	curr->ant_index = 0;
	curr->is_empty = TRUE;
	next->is_empty = FALSE;
	ft_printf("L%d-%s ", next->ant_index, next->name);
}

void	move_s2r(t_ways *way, int *ant_num, t_room *next)
{
	way->ants_in--;
	(*ant_num)++;
	next->ant_index = (*ant_num);
	next->is_empty = FALSE;
	ft_printf("L%d-%s ", next->ant_index, next->name);
}

void	move_s2e(t_ways *way, int *ant_num, t_room *next)
{
	way->ants_in--;
	(*ant_num)++;
	next->ant_count++;
	ft_printf("L%d-%s ", *ant_num, next->name);
}

void	move_r2e(t_room *curr, t_room *next)
{
	next->ant_count++;
	curr->is_empty = TRUE;
	ft_printf("L%d-%s ", curr->ant_index, next->name);
	curr->ant_index = 0;
}
