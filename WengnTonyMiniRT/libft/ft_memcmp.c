/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:57:39 by weng              #+#    #+#             */
/*   Updated: 2021/10/05 10:57:39 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Compares the first 'n' bytes (each interpreted as unsigned char) of the
memory areas 's1' and 's2'.
*/
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;

	if (n == 0)
		return (0);
	else
	{
		str1 = (unsigned char *) s1;
		str2 = (unsigned char *) s2;
		while (*str1 == *str2 && n-- > 1)
		{
			str1++;
			str2++;
		}
		return (*str1 - *str2);
	}	
}
