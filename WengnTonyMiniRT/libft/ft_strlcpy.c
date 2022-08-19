/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:58:12 by weng              #+#    #+#             */
/*   Updated: 2021/10/05 10:58:12 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Copies string. It is designed to be safer, more consistent, and less
error prone replacements for 'strncpy'. Unlike that function, strlcpy()
take the full size of the buffer (not just the length) and guarantee to
NUL-terminate the result (as long as 'size' is larger than 0). Note that
a byte for the NUL should be included in 'size'. Also note that
strlcpy() only operate on true "C" strings. This means that 'src' must
be NUL-terminated.

Copies up to 'size' - 1 characters from the NUL-terminated string 'src'
to 'dst', NUL-terminating the result.
*/
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	retval;

	retval = 0;
	while (*src != '\0' && dstsize > 1)
	{
		*dst++ = *src++;
		dstsize--;
		retval++;
	}
	if (dstsize != 0)
		*dst = '\0';
	while (*src++ != '\0')
		retval++;
	return (retval);
}
