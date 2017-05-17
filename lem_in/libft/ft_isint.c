/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 11:42:23 by apalanic          #+#    #+#             */
/*   Updated: 2016/11/25 11:43:40 by apalanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool			ft_isint(char *tmp)
{
	int			i;
	long long	n;
 
	i = 0;
	if (tmp[i] == '-' || tmp[i] == '+')
		i++;
	while (tmp[i] != '\0')
	{
		if (tmp[i] > '9' || tmp[i] < '0')
			return (FALSE);
		i++;
	}
	if (i > 11)
		return (FALSE);
	n = ft_atoll(tmp);
	if (n < INT_MIN || n > INT_MAX)
		return (FALSE);
	return (TRUE);
}
