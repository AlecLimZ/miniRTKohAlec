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

#include <time.h>
#include "miniRT.h"

// %ffps\n", 1.0 / ((double)(clock() - begin) / CLOCKS_PER_SEC));
// (double)(clock() - begin) / CLOCKS_PER_SEC);
void	benchmark(void)
{
	static double	begin = NAN;

	if (begin == NAN)
	{
		begin = clock();
	}
	else
	{
		printf("benchmark: %fs\n", (clock() - begin) / CLOCKS_PER_SEC);
		begin = NAN;
	}
}
