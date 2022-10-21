/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   benchmark.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:19:34 by Koh               #+#    #+#             */
/*   Updated: 2022/10/21 12:17:22 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

#ifdef __linux__
# include <time.h>
# include <math.h>
# include <stdio.h>

void	benchmark(const char *s)
{
	static double	begin = INFINITY;
	double			elapsed;

	if (begin == INFINITY)
	{
		begin = clock();
	}
	else
	{
		elapsed = (clock() - begin) / CLOCKS_PER_SEC;
		printf("%s: %.3fs %.1ffps\n", s, elapsed, 1 / elapsed);
		begin = INFINITY;
	}
}

#else

void	benchmark(const char *s)
{
	(void)s;
}

#endif
