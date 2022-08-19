/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 13:32:55 by hloke             #+#    #+#             */
/*   Updated: 2022/06/22 17:00:46 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

/* Handles the integral component of a number as a double, and moves
 * the pointer to the unhandled part of the string. */
static double	ft_atof_integral(const char **nptr)
{
	double	retval;
	int		sign;

	retval = 0;
	sign = 1;
	if (**nptr == '-')
		sign = -1;
	if (**nptr == '+' || **nptr == '-')
		++(*nptr);
	while (ft_isdigit(**nptr) == 1)
	{
		retval = retval * 10 + (**nptr - '0');
		++(*nptr);
	}
	return (sign * retval);
}

/* Convert string to a double. */
double	ft_atof(const char *nptr)
{
	double	retval;
	double	decimal;
	int		sign;

	sign = 1;
	if (*nptr == '-')
		sign = -1;
	if (*nptr == '+' || *nptr == '-')
		++nptr;
	retval = ft_atof_integral(&nptr);
	if (*nptr == '.')
	{
		decimal = 0.1;
		while (ft_isdigit(*(++nptr)) == 1)
		{
			retval += (*nptr - '0') * decimal;
			decimal /= 10;
		}
	}
	if (*nptr++ == 'e')
		return (sign * retval * pow(10, ft_atof_integral(&nptr)));
	else
		return (sign * retval);
}

/* Return 1 if the input string (optionally) starts with '+' or '-', the
 * remainder are all digits and at most one decimal point, 0 otherwise.
 */
int	ft_isdouble(const char *s)
{
	int	decimal;

	if (*s == '+' || *s == '-')
		++s;
	decimal = 0;
	while (decimal <= 1 && (ft_isdigit(*s) == 1 || *s == '.'))
	{
		if (*s == '.')
			++decimal;
		++s;
	}
	return (*s == '\0');
}

/* Return 1 if double is within min and max, inclusive, 0 otherwise.*/
int	ft_check_double(double d, double min, double max)
{
	return (min <= d && d <= max);
}

/* Check that the vector is of the specified size, and the values are
 * between min and max, inclusive. Maximum size supported is 4. */
t_vec	*ft_parse_vector(const char *s, size_t size, double min, double max)
{
	char	**arr;
	t_vec	*vec;
	int		retval;

	arr = ft_split_scene(s, ',');
	if (ft_array_size(arr) != size)
		ft_perror("Input vector is not the right size", EINVAL);
	vec = NULL;
	if (size != 0)
	{
		vec = ft_vec_new(size);
		vec->size = size;
		retval = 1;
		while (size > 0 && retval == 1)
		{
			retval = ft_isdouble(arr[--size]);
			vec->data[size] = ft_atof(arr[size]);
			retval &= ft_check_double(vec->data[size], min, max);
		}
		if (size != 0 || retval == 0)
			ft_perror("Invalid input vector", EINVAL);
	}
	ft_array_del(arr, free);
	return (vec);
}
