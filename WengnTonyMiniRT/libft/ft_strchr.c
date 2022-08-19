/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:58:01 by weng              #+#    #+#             */
/*   Updated: 2021/10/05 10:58:01 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Returns a pointer to the first occurrence of the character 'c' in the
string 's'.
*/
char	*ft_strchr(const char *s, int c)
{
	char	ch;

	ch = (char) c;
	while (1)
	{
		if (*s == ch)
			return ((char *) s);
		if (*s == '\0')
			return (0);
		s++;
	}
}
