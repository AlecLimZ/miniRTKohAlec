/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacklearn <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 21:27:59 by jacklearn         #+#    #+#             */
/*   Updated: 2021/05/12 09:49:12 by jacklearn        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*dst;
	const unsigned char	*src;
	size_t				i;

	dst = s1;
	src = s2;
	i = 0;
	if (n == 0)
		return (0);
	while (dst[i] == src[i] && i + 1 != n)
		i++;
	return (dst[i] - src[i]);
}
