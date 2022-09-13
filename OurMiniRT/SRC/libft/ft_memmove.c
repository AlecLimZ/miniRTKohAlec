/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacklearn <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 15:53:40 by jacklearn         #+#    #+#             */
/*   Updated: 2021/05/12 09:22:24 by jacklearn        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	unsigned char		*dst;
	const unsigned char	*src;
	size_t				i;

	dst = s1;
	src = s2;
	i = -1;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (dst > src)
		while (n--)
			dst[n] = src[n];
	else
		while (++i < n)
			dst[i] = src[i];
	return (s1);
}
