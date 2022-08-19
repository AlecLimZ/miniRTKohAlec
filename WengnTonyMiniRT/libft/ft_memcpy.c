/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:57:41 by weng              #+#    #+#             */
/*   Updated: 2021/10/05 10:57:41 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Copies 'n' bytes from memory area 'src' to memory area 'dest'. The
memory areas must not overlap. Use 'memmove' if the memory areas do
overlap.
*/
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*copy;
	const char	*s;

	copy = (char *) dest;
	s = (const char *) src;
	while (n-- > 0)
		*copy++ = *s++;
	return (dest);
}
