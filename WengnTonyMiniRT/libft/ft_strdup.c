/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:58:03 by weng              #+#    #+#             */
/*   Updated: 2021/10/05 10:58:04 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Returns a pointer to a new string which is a duplicate of the string 's'.
Memory for the new string is obtained with 'malloc', and can be freed
with 'free'.
*/
char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*retval;

	len = ft_strlen(s) + 1;
	retval = (char *) malloc(len * sizeof(char));
	if (retval != NULL)
		ft_strlcpy(retval, s, len);
	return (retval);
}
