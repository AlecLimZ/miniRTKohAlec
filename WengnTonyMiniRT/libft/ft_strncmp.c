/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:58:18 by weng              #+#    #+#             */
/*   Updated: 2021/10/05 10:58:18 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Compares only the first (at most) 'n' bytes of two strings 's1' and 's2'.
It returns an integer less than, equal to, or greater than zero if 's1'
is found, respectively, to be less than, to match, or be greater than
's2'.
*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;

	if (n == 0)
		return (0);
	else
	{
		str1 = (unsigned char *) s1;
		str2 = (unsigned char *) s2;
		while ((*str1 == *str2) && *str1 != '\0' && n-- > 1)
		{
			str1++;
			str2++;
		}
		return (*str1 - *str2);
	}
}
