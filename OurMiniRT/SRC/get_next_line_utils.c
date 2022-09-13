/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <leng-chu@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 21:52:08 by leng-chu          #+#    #+#             */
/*   Updated: 2021/12/03 12:03:59 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_free(char **str)
{
	if (*str && str)
	{
		free(*str);
		*str = NULL;
	}
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*sjoin;
	int		i;
	int		len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1);
	sjoin = (char *)malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!sjoin)
		return (NULL);
	i = -1;
	while (s1[++i])
		sjoin[i] = s1[i];
	i = -1;
	while (s2[++i])
		sjoin[len++] = s2[i];
	sjoin[len] = '\0';
	ft_free(&s1);
	return (sjoin);
}
