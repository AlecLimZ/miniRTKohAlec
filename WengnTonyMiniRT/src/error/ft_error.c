/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 10:34:22 by hloke             #+#    #+#             */
/*   Updated: 2022/06/22 17:11:17 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

/* Set the errno to n, print error and exit the program with error code 1. */
void	ft_perror(const char *s, int n)
{
	if (n != 0)
		errno = n;
	write(2, "Error\n", 6);
	perror(s);
	exit(EXIT_FAILURE);
}
