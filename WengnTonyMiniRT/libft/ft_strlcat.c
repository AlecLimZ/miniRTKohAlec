/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:58:10 by weng              #+#    #+#             */
/*   Updated: 2021/10/05 10:58:10 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Concatenates strings. It is designed to be safer, more consistent, and
less error prone replacements for 'strncat'. Unlike that function,
strlcat() take the full size of the buffer (not just the length) and
guarantee to NUL-terminate the result (as long as 'size' is larger than
0 or as long as there is at least one byte free in 'dst'). Note that a
byte for the NUL should be included in 'size'. Also note that
strlcat() only operate on true "C" strings. This means that both 'src'
and 'dst' must be NUL-terminated.

Appends the NUL-terminated string 'src' to the end of 'dst'. It will
append at most 'size' - strlen(dst) - 1 bytes, NUL-terminating the
result.
*/
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	retval;

	retval = 0;
	while (*dst != '\0' && size > 0)
	{
		dst++;
		size--;
		retval++;
	}
	while (*src != '\0' && size > 1)
	{
		*dst++ = *src++;
		size--;
		retval++;
	}
	if (size > 0)
		*dst = '\0';
	while (*src++ != '\0')
		retval++;
	return (retval);
}
