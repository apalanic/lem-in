/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apalanic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 16:06:56 by apalanic          #+#    #+#             */
/*   Updated: 2017/03/21 16:07:59 by apalanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		mem_realloc(t_get *node)
{
	char	*new;
	size_t	size;

	size = node->size_last + node->size_last;
	if ((new = ft_strnew(size)) == NULL)
		return (READ_ERROR);
	new = (char *)ft_memcpy(new, node->string, node->size_last);
	free(node->string);
	node->string = new;
	node->size_last *= 2;
	return (READ_SUCCESS);
}

static int		line_return(t_get *node, char **line)
{
	char	*tmp;
	size_t	i;

	i = 0;
	while ((node->string)[i] != '\n' && (node->string)[i] != '\0')
		i++;
	if ((*line = ft_strnew(i)) == NULL)
		return (READ_ERROR);
	*line = (char *)ft_memcpy(*line, node->string, i);
	if ((tmp = ft_strnew(node->size_last * 2)) == NULL)
		return (READ_ERROR);
	ft_strcpy(tmp, node->string + i + 1);
	ft_strdel(&(node->string));
	node->string = tmp;
	node->i = ft_strlen(node->string);
	return (READ_SUCCESS);
}

static int		read_line(const int fd, t_get *n, char **line)
{
	int		b;
	char	buf[BUFF_SIZE + 1];

	ft_bzero(buf, BUFF_SIZE + 1);
	while (!ft_strchr(n->string, '\n') && ((b = read(fd, buf, BUFF_SIZE)) > 0))
	{
		if (n->i + b >= n->size_last)
			if (!mem_realloc(n))
				return (READ_ERROR);
		ft_strncpy(n->string + n->i, buf, b);
		n->i += b;
		if (ft_strchr(n->string, '\n'))
		{
			if (line_return(n, line))
				return (READ_SUCCESS);
			else
				return (READ_ERROR);
		}
		ft_bzero(buf, BUFF_SIZE + 1);
	}
	if (!b && !ft_strlen(n->string + n->size_next) && (*line = ft_strdup("")))
		return (READ_COMPLETE);
	else
		return (line_return(n, line));
}

static t_get	*push_back(int fd)
{
	t_get	*ret;

	if ((ret = (t_get *)malloc(sizeof(t_get))) == NULL)
		return (NULL);
	if ((ret->string = ft_strnew(BUFF_SIZE)))
	{
		ret->i = 0;
		ret->size_last = BUFF_SIZE;
		ret->size_next = 0;
		ret->fd = fd;
		ret->next = NULL;
		return (ret);
	}
	return (NULL);
}

int				get_next_line(const int fd, char **line)
{
	static t_get	*tmp;
	int				res;
	t_get			*curr;

	res = 1;
	if (line == NULL)
		return (READ_ERROR);
	if (fd < 0 || BUFF_SIZE < 0 || (read(fd, 0, 0) == -1))
		res = 0;
	if (tmp == NULL)
		if ((tmp = push_back(fd)) == NULL)
			res = 0;
	curr = tmp;
	while (curr && res)
	{
		if (curr->fd == fd)
			return (read_line(fd, curr, line));
		if (curr->next == NULL && ((curr->next = push_back(fd)) != NULL))
			return (read_line(fd, curr->next, line));
		curr = curr->next;
	}
	if (!res)
		*line = ft_strdup("");
	return (READ_ERROR);
}
