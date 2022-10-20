/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:19:34 by Koh               #+#    #+#             */
/*   Updated: 2022/09/18 11:18:10 by Koh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

#ifdef __linux__
#include <time.h>
#include <stdio.h>

void	benchmark(void)
{
	static double	begin = INFINITY;

	if (begin == INFINITY)
	{
		begin = clock();
	}
	else
	{
		printf("benchmark: %fs\n", (clock() - begin) / CLOCKS_PER_SEC);
		begin = INFINITY;
	}
}

#else

void	benchmark(void)
{
}

#endif
