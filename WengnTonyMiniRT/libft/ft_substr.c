/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:58:34 by weng              #+#    #+#             */
/*   Updated: 2021/10/05 10:58:34 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Allocates (with malloc(3)) and returns a substring from the string 's'.
The substring begins at index 'start' and is of maximum size 'len'.
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*retval;
	size_t	len_s;

	if (start >= ft_strlen(s))
		len = 0;
	else
	{
		s += start;
		len_s = ft_strlen(s);
		if (len > len_s)
			len = len_s;
	}
	retval = malloc((len + 1) * sizeof(char));
	if (retval != NULL)
		ft_strlcpy(retval, s, len + 1);
	return (retval);
}
