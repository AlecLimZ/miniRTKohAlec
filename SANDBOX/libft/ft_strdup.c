/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacklearn <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:48:15 by jacklearn         #+#    #+#             */
/*   Updated: 2021/05/14 15:06:52 by jacklearn        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*m;

	m = (char *)malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (m == 0)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		m[i] = s1[i];
		i++;
	}
	m[i] = '\0';
	return (m);
}
