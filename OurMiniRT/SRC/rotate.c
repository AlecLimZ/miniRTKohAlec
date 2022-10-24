/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:19:34 by Koh               #+#    #+#             */
/*   Updated: 2022/10/25 07:40:08 by Koh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

void	rotate_x(float *y, float *z, double radian_x)
{
	const float	y_ = *y;

	*y = y_ * cos(radian_x) - *z * sin(radian_x);
	*z = y_ * sin(radian_x) + *z * cos(radian_x);
}

void	rotate_y(float *x, float *z, double radian_y)
{
	const float	x_ = *x;

	*x = x_ * cos(radian_y) + *z * sin(radian_y);
	*z = -x_ * sin(radian_y) + *z * cos(radian_y);
}
