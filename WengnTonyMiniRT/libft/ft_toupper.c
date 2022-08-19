/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:58:39 by weng              #+#    #+#             */
/*   Updated: 2021/10/05 10:58:39 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
If 'c' is a lowercase letter, returns its uppercase equivalent,
Otherwise, returns 'c'.
*/
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 'a' + 'A');
	else
		return (c);
}
