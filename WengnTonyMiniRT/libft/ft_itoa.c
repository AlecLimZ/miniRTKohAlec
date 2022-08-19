/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:56:53 by weng              #+#    #+#             */
/*   Updated: 2021/10/05 10:56:54 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Allocates (with malloc(3)) and returns a string representing the integer
received as an argument. Negative numbers must be handled.
*/
char	*ft_itoa(int n)
{
	return (ft_lltoa_base((long long) n, "0123456789"));
}
