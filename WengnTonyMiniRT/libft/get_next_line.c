/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:32:49 by weng              #+#    #+#             */
/*   Updated: 2021/12/14 13:41:51 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Create a buffer for a particular file descriptor */
static t_buffer	*set_buffer(int fd)
{
	t_buffer	*buffer;

	buffer = malloc(sizeof(t_buffer));
	if (buffer != NULL)
	{
		buffer->fd = fd;
		buffer->offset = BUFFER_SIZE;
		buffer->remainder = 0;
		buffer->next = NULL;
		buffer->buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (buffer->buf == NULL)
		{
			free(buffer);
			return (NULL);
		}
		else
			buffer->buf[BUFFER_SIZE] = '\0';
	}
	return (buffer);
}

/*
Return an existing corresponding buffer from the list, or add and return
a new corresponding buffer.
*/
static t_buffer	*get_buffer(t_buffer **lst, int fd)
{
	t_buffer	*buffer;
	t_buffer	*new;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buffer = *lst;
	while (buffer != NULL)
	{
		if (buffer->fd == fd)
			return (buffer);
		buffer = buffer->next;
	}
	new = set_buffer(fd);
	if (new != NULL)
	{
		new->next = *lst;
		*lst = new;
	}
	return (new);
}

/* Delete a corresponding buffer from a list of buffers. */
static void	del_buffer(t_buffer **lst, int fd)
{
	t_buffer	*prev;
	t_buffer	*buffer;

	prev = NULL;
	buffer = *lst;
	while (buffer != NULL && buffer->fd != fd)
	{
		prev = buffer;
		buffer = buffer->next;
	}
	if (buffer == NULL)
		return ;
	if (prev == NULL)
		*lst = buffer->next;
	else
		prev->next = buffer->next;
	free(buffer->buf);
	free(buffer);
}

char	*get_next_line(int fd)
{
	static t_buffer	*lst = NULL;
	t_buffer		*buffer;
	char			*retval;
	char			*end;

	buffer = get_buffer(&lst, fd);
	if (buffer == NULL)
		return (NULL);
	retval = NULL;
	end = NULL;
	while (end == NULL)
	{
		ft_read_from_file(fd, buffer);
		if (buffer->remainder <= 0)
			break ;
		end = ft_strchr(buffer->buf + buffer->offset, '\n');
		retval = ft_read_from_buffer(retval, buffer, end);
	}
	if (retval == NULL)
		del_buffer(&lst, fd);
	return (retval);
}
