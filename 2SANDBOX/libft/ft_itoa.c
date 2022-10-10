/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jacklearn <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/17 18:06:07 by jacklearn         #+#    #+#             */
/*   Updated: 2021/05/17 19:50:41 by jacklearn        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_numlen(int n)
{
	int				len;
	unsigned int	i;

	if (n == 0)
		return (1);
	len = 0;
	i = n;
	if (n < 0)
	{
		len++;
		i = -i;
	}
	while (i > 0)
	{
		i /= 10;
		len++;
	}
	return (len);
}

int	ft_isneg(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

char	*ft_itoa(int n)
{
	char			*newc;
	int				len;
	unsigned int	i;

	len = ft_numlen(n);
	newc = (char *)malloc(sizeof(char) * (len + 1));
	if (!newc)
		return (NULL);
	newc[len] = '\0';
	i = n;
	if (ft_isneg(n))
	{
		newc[0] = '-';
		i = -n;
	}
	len--;
	while (len >= ft_isneg(n))
	{
		newc[len] = i % 10 + '0';
		i /= 10;
		len--;
	}
	return (newc);
}
