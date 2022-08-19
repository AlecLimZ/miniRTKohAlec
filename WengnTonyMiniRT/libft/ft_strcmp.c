/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:25:51 by weng              #+#    #+#             */
/*   Updated: 2022/01/13 11:33:37 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Returns an integer less than, equal to, or greater than zero if 's1'
is found, respectively, to be less than, to match, or be greater than
's2'.
*/
int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	while ((*str1 == *str2) && *str1 != '\0')
	{
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}
