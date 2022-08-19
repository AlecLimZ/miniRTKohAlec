/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:58:16 by weng              #+#    #+#             */
/*   Updated: 2021/10/05 10:58:16 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Applies the function 'f' to each character of the string 's' to create
a new string (with malloc(3)) resulting from successive applications of
'f'.
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*retval;
	char			*copy;
	unsigned int	i;

	if (s == NULL || f == NULL)
		return (NULL);
	retval = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (retval != NULL)
	{
		copy = retval;
		i = 0;
		while (*s != '\0')
			*copy++ = f(i++, *s++);
		*copy = '\0';
	}
	return (retval);
}
