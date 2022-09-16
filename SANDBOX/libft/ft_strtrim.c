/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacklearn <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 11:53:19 by jacklearn         #+#    #+#             */
/*   Updated: 2021/05/17 13:55:09 by jacklearn        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	getlen(char const *s1, char const *set)
{
	int	len;
	int	i;
	int	j;

	len = ft_strlen(s1);
	i = 0;
	j = len - 1;
	while (i < len && ft_strchr(set, s1[i]))
	{
		i++;
		len--;
	}
	while (j >= 0 && ft_strchr(set, s1[j]))
	{
		j--;
		len--;
	}
	if (len < 0)
		len = 0;
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	int		i;
	int		len;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	len = getlen(s1, set);
	trim = (char *)malloc(sizeof(char) * (len + 1));
	if (trim == 0)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	while (len--)
		trim[i++] = *s1++;
	trim[i] = '\0';
	return (trim);
}
