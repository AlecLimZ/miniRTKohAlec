/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacklearn <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 15:09:28 by jacklearn         #+#    #+#             */
/*   Updated: 2021/05/12 09:16:24 by jacklearn        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *s1, const void *s2, int c, size_t n)
{
	size_t				i;
	unsigned char		find;
	unsigned char		*dst;
	const unsigned char	*src;

	i = -1;
	find = c;
	dst = s1;
	src = s2;
	while (++i < n)
	{
		dst[i] = src[i];
		if (src[i] == find)
			return (dst + i + 1);
	}
	return (NULL);
}
