/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 01:57:51 by Koh               #+#    #+#             */
/*   Updated: 2022/09/15 02:35:51 by Koh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// int	pull_str(char **s, int (*f)(int), char **begin, char **end)
// {
// 	const char	*s_ = *s;

// 	if (begin)
// 		*begin = *s;
// 	while (**s && f(**s))
// 		++*s;
// 	if (end)
// 		*end = *s;
// 	return (*s - s_);
// }

int	trim_chr(char **s, char c)
{
	const char	*s_ = *s;

	while (**s && **s == c)
		++*s;
	return (*s - s_);
}

int	trim_str(char **s, int (*f)(int))
{
	const char	*s_ = *s;

	while (**s && f(**s))
		++*s;
	return (*s - s_);
}

int	pull_nbr(char **line, double *d, double min, double max)
{
	const char	*begin = *line;

	if (trim_chr(line, '-') <= 1
		&& trim_str(line, ft_isdigit) >= 1
		&& trim_chr(line, '.') <= 1
		&& trim_str(line, ft_isdigit) >= 0
	)
	{
		*d = parse_double(begin);
		return (*d >= min && *d <= max);
	}
	return (0);
}

int	pull_vec(char **line, t_vec3 *d, double min, double max)
{
	return (
		pull_nbr(line, &d->x, min, max) == 1
		&& trim_chr(line, ',') == 1
		&& pull_nbr(line, &d->y, min, max) == 1
		&& trim_chr(line, ',') == 1
		&& pull_nbr(line, &d->z, min, max) == 1
	);
}

int	pull_rgb(char **line, t_vec3 *d)
{
	if (
		pull_nbr(line, &d->x, 0, 255) == 1
		&& trim_chr(line, ',') == 1
		&& pull_nbr(line, &d->y, 0, 255) == 1
		&& trim_chr(line, ',') == 1
		&& pull_nbr(line, &d->z, 0, 255) == 1
	)
	{
		d->r /= 255.0;
		d->g /= 255.0;
		d->b /= 255.0;
		return (1);
	}
	return (0);
}
