/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:56:04 by weng              #+#    #+#             */
/*   Updated: 2021/10/05 10:56:06 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Erases the data in the 'n' bytes of the memory starting at the location
pointed to by 's', by writing zeros (bytes containing '\0') to that area.
*/
void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}
