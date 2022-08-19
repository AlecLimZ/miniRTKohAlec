/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:58:32 by weng              #+#    #+#             */
/*   Updated: 2021/10/05 10:58:32 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Allocates (with malloc(3)) and returns a copy of 's1' with the
characters specified in 'set' removed from the beginning and the end of
the string.
*/
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*first;
	char	*retval;
	size_t	len;

	while (*s1 != '\0' && ft_strchr(set, *s1) != NULL)
		s1++;
	first = (char *) s1;
	while (*s1 != '\0')
		s1++;
	while (s1 > first && (*s1 == '\0' || ft_strchr(set, *s1) != NULL))
		s1--;
	if (*s1 == '\0')
		len = 0;
	else
		len = s1 - first + 1;
	retval = malloc((len + 1) * sizeof(char));
	if (retval != NULL)
		ft_strlcpy(retval, first, len + 1);
	return (retval);
}
