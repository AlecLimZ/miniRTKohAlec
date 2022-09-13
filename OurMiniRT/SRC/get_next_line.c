/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <leng-chu@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 21:52:26 by leng-chu          #+#    #+#             */
/*   Updated: 2021/12/03 12:04:51 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

size_t	ft_strlen_c(const char *s, const char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

int	result(int nrd, char **buff, char **line)
{
	char			*temp;

	if (nrd < 0)
		return (-1);
	*line = ft_substr(*buff, 0, ft_strlen_c(*buff, '\n'));
	if (!line)
		return (-1);
	if (ft_strchr(*buff, '\n'))
	{
		temp = ft_strdup(ft_strchr(*buff, '\n') + 1);
		ft_free(&*buff);
		*buff = temp;
		return (1);
	}
	ft_free(&*buff);
	return (0);
}

int	ft_checkbuff(char **buff)
{
	if (!*buff)
	{
		*buff = ft_strdup("");
		if (!*buff)
			return (0);
	}
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*linebuff[OPEN_MAX];
	char		*newline;
	int			readbts;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > OPEN_MAX || !line)
		return (-1);
	if (!(ft_checkbuff(&linebuff[fd])))
		return (-1);
	newline = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!newline)
		return (-1);
	readbts = 1;
	while (readbts > 0)
	{
		readbts = read(fd, newline, BUFFER_SIZE);
		newline[readbts] = '\0';
		linebuff[fd] = ft_strjoin_free(linebuff[fd], newline);
		if (ft_strchr(linebuff[fd], '\n'))
			break ;
	}
	ft_free(&newline);
	return (result(readbts, &linebuff[fd], line));
}
