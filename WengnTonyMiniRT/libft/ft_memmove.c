/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:57:43 by weng              #+#    #+#             */
/*   Updated: 2021/10/05 10:57:44 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Copies 'n' bytes from memory area 'src' to memory area 'dest'. The
memory areas may overlap: copying takes place as though the bytes in
'src' are first copied into a temporary array that does not overlap
'src' or 'dest', and the bytes are then copied from the temporary array
to 'dest'.
*/
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	d = (char *) dest;
	s = (const char *) src;
	if (s > d)
	{
		while (n-- > 0)
			*d++ = *s++;
	}
	else
	{
		d += n - 1;
		s += n - 1;
		while (n-- > 0)
			*d-- = *s--;
	}
	return (dest);
}
