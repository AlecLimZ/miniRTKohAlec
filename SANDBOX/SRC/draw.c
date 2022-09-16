/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:45:06 by leng-chu          #+#    #+#             */
/*   Updated: 2022/09/16 13:04:30 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	rgbtohex2(double a, double r, double g, double b)
{
	int	ac;
	int	rc;
	int	gc;
	int	bc;

	ac = (int)(255.999 * a);
	rc = (int)(255.999 * r);
	gc = (int)(255.999 * g);
	bc = (int)(255.999 * b);
	return ((ac << 24) + (rc << 16) + (gc << 8) + bc);
}

void	ft_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->len + x * (data->px / 8));
	*(int *)dst = color;
}
