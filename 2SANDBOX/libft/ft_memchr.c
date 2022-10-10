/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacklearn <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:03:12 by jacklearn         #+#    #+#             */
/*   Updated: 2021/05/11 17:12:05 by jacklearn        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*dst;
	unsigned char		w;
	size_t				i;
	const unsigned char	*ptr;

	dst = s;
	w = c;
	i = -1;
	while (++i < n)
	{
		if (dst[i] == w)
		{
			ptr = &dst[i];
			return ((unsigned char *)ptr);
		}
	}
	return (NULL);
}
