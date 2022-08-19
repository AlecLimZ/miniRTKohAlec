/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:55:28 by weng              #+#    #+#             */
/*   Updated: 2021/10/05 10:55:30 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Converts the initial portion of the string pointed to by 'nptr' to int. */
int	ft_atoi(const char *nptr)
{
	int	sign;
	int	retval;

	sign = 1;
	retval = 0;
	while (ft_isspace(*nptr) == 1)
		nptr++;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (ft_isdigit(*nptr) == 1)
	{
		retval *= 10;
		retval += *nptr - '0';
		nptr++;
	}
	return (retval * sign);
}
