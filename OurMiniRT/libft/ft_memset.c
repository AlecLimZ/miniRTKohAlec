/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacklearn <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 18:35:35 by jacklearn         #+#    #+#             */
/*   Updated: 2021/05/10 21:27:24 by jacklearn        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	a;
	size_t			i;
	unsigned char	*dst;

	a = c;
	i = 0;
	dst = s;
	while (i < n)
		dst[i++] = a;
	return (dst);
}
