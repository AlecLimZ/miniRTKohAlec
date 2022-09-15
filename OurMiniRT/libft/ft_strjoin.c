/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacklearn <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 11:23:58 by jacklearn         #+#    #+#             */
/*   Updated: 2021/05/17 13:43:11 by jacklearn        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*sjoin;
	int		i;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	sjoin = (char *)malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!sjoin)
		return (NULL);
	while (*s1)
		sjoin[i++] = *s1++;
	while (*s2)
		sjoin[i++] = *s2++;
	sjoin[i] = '\0';
	return (sjoin);
}
