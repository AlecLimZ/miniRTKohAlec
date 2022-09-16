/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacklearn <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 16:26:07 by jacklearn         #+#    #+#             */
/*   Updated: 2021/05/17 21:42:23 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_totalwords(char const *s, char c)
{
	int	totalw;
	int	checkw;

	totalw = 0;
	checkw = 0;
	while (*s)
	{
		if (*s != c && checkw == 0)
		{
			checkw = 1;
			totalw++;
		}
		else if (*s == c && checkw == 1)
			checkw = 0;
		s++;
	}
	return (totalw);
}

int	ft_lengthword(char const *s, char c)
{
	int	len;

	len = 0;
	while (*s != c && *s)
	{
		s++;
		len++;
	}
	return (len);
}

void	*ft_freefail(char **newsp, int i)
{
	while (i--)
		free(newsp[i]);
	free(newsp);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**newsp;
	int		i;
	int		tw;
	int		wlen;

	if (!s)
		return (NULL);
	tw = ft_totalwords(s, c);
	newsp = (char **)malloc(sizeof(char *) * (tw + 1));
	if (!newsp)
		return (NULL);
	i = 0;
	while (tw--)
	{
		while (*s == c && *s)
			s++;
		wlen = ft_lengthword(s, c);
		newsp[i] = ft_substr(s, 0, wlen);
		if (newsp == 0)
			return (ft_freefail(newsp, i));
		s += wlen;
		i++;
	}
	newsp[i] = NULL;
	return (newsp);
}
