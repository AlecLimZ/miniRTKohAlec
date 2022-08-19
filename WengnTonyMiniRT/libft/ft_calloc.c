/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:56:12 by weng              #+#    #+#             */
/*   Updated: 2021/10/05 10:56:13 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Allocates memory for an array of 'nmemb' elements of 'size' bytes each
and returns a pointer to the allocated memory. The memory is set to zero.
If 'nmemb' or 'size' is 0, then calloc() returns either NULL, or a
unique pointer value that can later be successfully passed to free(). If
the multiplication of 'nmemb' and 'size' would result in integer
overflow, then calloc() returns an error.
*/
void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	mul;
	void	*retval;

	mul = nmemb * size;
	if (nmemb != 0 && size != 0 && mul / size != nmemb)
		return (NULL);
	retval = malloc(mul);
	if (retval != NULL)
		ft_bzero(retval, mul);
	return (retval);
}
