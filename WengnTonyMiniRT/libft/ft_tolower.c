/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:58:37 by weng              #+#    #+#             */
/*   Updated: 2021/10/05 10:58:37 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
If 'c' is an uppercase letter, returns its lowercase equivalent.
Otherwise, returns 'c'.
*/
int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c - 'A' + 'a');
	else
		return (c);
}
