/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:58:28 by weng              #+#    #+#             */
/*   Updated: 2021/10/05 10:58:29 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Returns a pointer to the last occurrence of the character 'c' in the
string 's'.
*/
char	*ft_strrchr(const char *s, int c)
{
	char	*current;
	char	*next;

	if ((char) c == '\0')
		return (ft_strchr(s, c));
	current = NULL;
	next = ft_strchr(s, c);
	while (next != NULL)
	{
		current = next;
		next = ft_strchr(next + 1, c);
	}
	return (current);
}
