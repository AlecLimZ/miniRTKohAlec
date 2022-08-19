/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:57:36 by weng              #+#    #+#             */
/*   Updated: 2021/10/05 10:57:36 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Scans the initial 'n' bytes of the memory area pointed to by 's' for the
first instance of 'c'. Both 'c' and the bytes of the memory area pointed
to by 's' are interpreted as unsigned char.
*/
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	l;

	str = (unsigned char *) s;
	l = (unsigned char) c;
	while (n-- > 0)
	{
		if (*str == l)
			return (str);
		str++;
	}
	return (NULL);
}
