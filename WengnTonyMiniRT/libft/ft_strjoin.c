/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:58:08 by weng              #+#    #+#             */
/*   Updated: 2021/10/05 10:58:08 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 
Allocates (with malloc(3)) and returns a new string, which is the result
of the concatenation of 's1' and 's2'.
*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*retval;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	retval = malloc((len1 + len2 + 1) * sizeof(char));
	if (retval != NULL)
	{
		*retval = '\0';
		ft_strlcat(retval, s1, len1 + 1);
		ft_strlcat(retval, s2, len1 + len2 + 1);
	}
	return (retval);
}
