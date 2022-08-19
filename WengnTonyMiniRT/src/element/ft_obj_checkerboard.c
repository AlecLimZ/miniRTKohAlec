/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_checkerboard.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 11:13:38 by weng              #+#    #+#             */
/*   Updated: 2022/06/10 13:41:41 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "element.h"

/* return a checkerboard colour on a cone, given a point on the local view */
t_vec	*ft_cone_checkerboard(t_obj *cone, t_vec *point)
{
	int		steps;
	double	angle;
	double	phi;

	(void) cone;
	steps = (2 * M_PI * 1) / 0.5;
	steps = steps - (steps % 2);
	angle = 360.0 / steps * M_PI / 180;
	phi = atan2(point->data[1], point->data[0]);
	steps = (int)(point->data[2] / 0.5) + (int)(phi / angle)
		+ (point->data[1] < 0) + (point->data[2] < 0);
	if (steps % 2 == 0)
		return (ft_vec3_new(0.75, 0.75, 0.75));
	else
		return (ft_vec3_new(0.25, 0.25, 0.25));
}

/* return a checkerboard colour on a cylinder given a point on the local view */
t_vec	*ft_cylinder_checkerboard(t_obj *cy, t_vec *point)
{
	int		steps;
	double	angle;
	double	phi;

	steps = (2 * M_PI * cy->dimension->data[0]) / 0.5;
	steps = steps - (steps % 2);
	angle = 360.0 / steps * M_PI / 180;
	phi = atan2(point->data[1], point->data[0]);
	steps = (int)(point->data[2] / 0.5) + (int)(phi / angle)
		+ (point->data[1] < 0) + (point->data[2] < 0);
	if (steps % 2 == 0)
		return (ft_vec3_new(0.75, 0.75, 0.75));
	else
		return (ft_vec3_new(0.25, 0.25, 0.25));
}

/* return a checkerboard colour on a plane, given a point on the local view */
t_vec	*ft_plane_checkerboard(t_obj *plane, t_vec *point)
{
	int	steps;

	(void) plane;
	steps = (int)(point->data[0] / 0.5) + (int)(point->data[1] / 0.5)
		+ (point->data[0] < 0) + (point->data[1] < 0);
	if (steps % 2 == 0)
		return (ft_vec3_new(0.75, 0.75, 0.75));
	else
		return (ft_vec3_new(0.25, 0.25, 0.25));
}

/* return a checkerboard colour on a sphere, given a point on the local view */
t_vec	*ft_sphere_checkerboard(t_obj *sp, t_vec *point)
{
	int		steps;
	double	angle;
	double	theta;
	double	phi;

	steps = (2 * M_PI * sp->dimension->data[0]) / 0.5;
	steps = steps - (steps % 2);
	angle = 360.0 / steps * M_PI / 180;
	theta = acos(point->data[2] / sp->dimension->data[0]);
	phi = atan2(point->data[1], point->data[0]);
	steps = (int)(theta / angle) + (int)(phi / angle) + (point->data[1] < 0);
	if (steps % 2 == 0)
		return (ft_vec3_new(0.75, 0.75, 0.75));
	else
		return (ft_vec3_new(0.25, 0.25, 0.25));
}
