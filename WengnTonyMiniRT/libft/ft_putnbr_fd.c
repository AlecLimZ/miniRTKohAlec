/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:57:54 by weng              #+#    #+#             */
/*   Updated: 2021/10/05 10:57:54 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Outputs the integer 'n' to the given file descriptor. */
void	ft_putnbr_fd(int n, int fd)
{
	char	*nbr;

	nbr = ft_itoa(n);
	ft_putstr_fd(nbr, fd);
	free(nbr);
}
