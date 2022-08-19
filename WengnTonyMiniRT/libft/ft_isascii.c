/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:56:38 by weng              #+#    #+#             */
/*   Updated: 2021/10/05 10:56:39 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Checks whether c is a 7-bit unsigned char value that fits into the ASCII
character set.
*/
int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
