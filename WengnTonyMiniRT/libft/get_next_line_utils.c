/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 13:32:44 by weng              #+#    #+#             */
/*   Updated: 2021/12/14 13:38:27 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Read from file and updates the buffer if required. */
void	ft_read_from_file(int fd, t_buffer *buffer)
{
	if (buffer->remainder == 0)
	{
		buffer->remainder = read(fd, buffer->buf, BUFFER_SIZE);
		if (buffer->remainder >= 0)
			buffer->buf[buffer->remainder] = '\0';
		buffer->offset = 0;
	}
}

char	*ft_read_from_buffer(char *s, t_buffer *buffer, char *end)
{
	char	*retval;
	size_t	len1;
	size_t	len2;
	size_t	new_len;

	len1 = 0;
	if (s != NULL)
		len1 = ft_strlen(s);
	if (end == NULL)
		len2 = buffer->remainder;
	else
		len2 = end - (buffer->buf + buffer->offset) + 1;
	new_len = len1 + len2 + 1;
	retval = malloc(new_len * sizeof(char));
	if (retval != NULL)
	{
		if (s != NULL)
			ft_strlcpy(retval, s, new_len);
		ft_strlcpy(retval + len1, buffer->buf + buffer->offset, len2 + 1);
		buffer->offset += len2;
		buffer->remainder -= len2;
	}
	if (s != NULL)
		free(s);
	return (retval);
}
