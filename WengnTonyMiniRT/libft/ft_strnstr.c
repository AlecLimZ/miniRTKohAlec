/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:58:22 by weng              #+#    #+#             */
/*   Updated: 2021/10/05 10:58:25 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Locates the first occurrence of the null-terminated string 'little' in
the string 'big', where not more than 'len' characters are searched.
Characters that appear after a '\0' character are not searched.
*/
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_len;

	if (*little == '\0')
		return ((char *) big);
	little_len = ft_strlen(little);
	while (*big != '\0' && len-- >= little_len)
	{
		if (ft_strncmp(big, little, little_len) == 0)
			return ((char *) big);
		big++;
	}
	return (NULL);
}
