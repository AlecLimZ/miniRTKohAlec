/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 10:58:41 by weng              #+#    #+#             */
/*   Updated: 2022/05/25 14:22:29 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// verify base characters. No repeat, no + or -. More than 1. 
// Return the number of characters if valid, 0 otherwise.
// Assuming any printable characters can be used as base, other that + or -.
static int	verify_base(char *base)
{
	int		len;

	len = ft_strlen(base);
	if (len < 2)
		return (0);
	while (*base != '\0')
	{
		if (ft_strchr(base + 1, *base) != 0)
			return (0);
		base++;
	}
	return (len);
}

static void	ft_lltoa_base_aux(
		long long n, char *base, long long baselen, char *s)
{
	int		r;
	char	*ptr;

	if (n <= -baselen || n >= baselen)
		ft_lltoa_base_aux(n / baselen, base, baselen, s);
	r = n % baselen;
	if (r < 0)
		r *= -1;
	ptr = s;
	while (*ptr != '\0')
		ptr++;
	*ptr = base[r];
}

/*
Allocates (with malloc(3)) and returns a string representing the long long
received as an argument. Negative numbers must be handled.
*/
char	*ft_lltoa_base(long long n, char *base)
{
	char		*retval;
	char		*str;
	long long	baselen;

	baselen = verify_base(base);
	if (baselen == 0)
		return (NULL);
	str = ft_calloc(8 * sizeof(long long) + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	if (n < 0)
		*str = '-';
	ft_lltoa_base_aux(n, base, baselen, str);
	retval = ft_strdup(str);
	free(str);
	return (retval);
}

static void	ft_ulltoa_base_aux(
		unsigned long long n, char *base, unsigned long long baselen, char *s)
{
	int		r;
	char	*ptr;

	if (n >= baselen)
		ft_ulltoa_base_aux(n / baselen, base, baselen, s);
	r = n % baselen;
	ptr = s;
	while (*ptr != '\0')
		ptr++;
	*ptr = base[r];
}

/*
Allocates (with malloc(3)) and returns a string representing the unsigned
long long received as an argument.
*/
char	*ft_ulltoa_base(unsigned long long n, char *base)
{
	char				*retval;
	char				*str;
	unsigned long long	baselen;

	baselen = verify_base(base);
	if (baselen == 0)
		return (NULL);
	str = ft_calloc(8 * sizeof(unsigned long long) + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_ulltoa_base_aux(n, base, baselen, str);
	retval = ft_strdup(str);
	free(str);
	return (retval);
}
