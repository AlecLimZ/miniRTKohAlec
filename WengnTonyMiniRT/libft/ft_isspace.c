/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:56:48 by weng              #+#    #+#             */
/*   Updated: 2021/10/05 10:56:51 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Checks for white-space characters, which are: space, form-feed ('\f'),
newline ('\n'), carriage return ('\r'), horizontal tab ('\t'),
and vertical tab ('\v').
*/
int	ft_isspace(int c)
{
	char	c_;

	c_ = (char) c;
	return (c_ == ' ' || c_ == '\f' || c_ == '\n' || c_ == '\r'
		|| c_ == '\t' || c_ == '\v');
}
