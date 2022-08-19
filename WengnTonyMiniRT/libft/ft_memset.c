/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:57:46 by weng              #+#    #+#             */
/*   Updated: 2021/10/05 10:57:46 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Fills the first 'n' bytes of the memory area pointed to by 's' with the
constant byte 'c'.
*/
void	*ft_memset(void *b, int c, size_t len)
{
	char	*s;
	char	c_;

	s = (char *) b;
	c_ = (char) c;
	while (len-- > 0)
		*s++ = c_;
	return (b);
}
