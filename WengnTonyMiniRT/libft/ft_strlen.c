/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:58:14 by weng              #+#    #+#             */
/*   Updated: 2021/10/05 10:58:14 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Calculates the length of the string pointed to by 's', excluding the
terminating null byte ('\0').
*/
size_t	ft_strlen(const char *s)
{
	const char	*str;

	str = s;
	while (*str != '\0')
		str++;
	return (str - s);
}
