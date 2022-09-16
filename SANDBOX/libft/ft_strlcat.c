/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacklearn <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 14:56:55 by jacklearn         #+#    #+#             */
/*   Updated: 2021/05/10 18:17:28 by jacklearn        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	l_dst;
	size_t	l_src;
	size_t	i;

	l_dst = ft_strlen(dst);
	l_src = ft_strlen(src);
	if (dstsize == 0)
		return (l_src);
	else if (l_dst >= dstsize)
		return (dstsize + l_src);
	i = 0;
	while (src[i] && l_dst + i < (dstsize - 1))
	{
		dst[l_dst + i] = src[i];
		i++;
	}
	dst[l_dst + i] = '\0';
	return (l_dst + l_src);
}
