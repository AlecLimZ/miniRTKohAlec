/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 02:05:56 by Koh               #+#    #+#             */
/*   Updated: 2022/09/18 14:10:17 by Koh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "parser.h"

double	ft_strtod(const char *str, char **endptr)
{
	const char	*c = str;
	double		value;
	int			decimal_place;
	int			has_digits;
	int			is_neg;

	has_digits = 0;
	value = 0.0;
	while (ft_isspace(*c))
		++c;
	is_neg = ((*c == '+' || *c == '-') && *c++ == '-');
	while (ft_isdigit(*c) && ++has_digits)
		value = value * 10 + (*c++ - '0');
	decimal_place = 0;
	if (*c == '.' && (ft_isdigit(c[1]) || has_digits) && *c++)
		while (ft_isdigit(*c) && ++has_digits)
			value += pow(.1, ++decimal_place) * (*c++ - '0');
	if (endptr && has_digits)
		*endptr = (char *)c;
	else if (endptr)
		*endptr = (char *)str;
	if (is_neg)
		return (-value);
	else
		return (value);
}

int	ft_isspace(int c)
{
	return (c == ' ' || ('\t' <= c && c <= '\r'));
}
