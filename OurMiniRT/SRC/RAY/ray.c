/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <leng-chu@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:44:43 by leng-chu          #+#    #+#             */
/*   Updated: 2022/09/17 14:45:13 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vecray.h"

void	ray_init(t_ray *ray, const t_point3 *origin, const t_vec3 *direction)
{
	ray->orig = *origin;
	ray->dir = *direction;
}

//return type point3 (where is point3 at)
// orig & dir is belonging to t_ray struct
//return orig + (t * dir)
// (t * dir) is new vec3
// orig + new vec3 will create another new point3
// which is give the position that it is at
t_point3	get_at(t_ray *ray, const double t)
{
	t_vec3		v1;
	t_point3	new;

	v1 = new_xv(t, &ray->dir);
	new = new_plus2v(&ray->orig, &v1);
	return (new);
}

t_color	ray_color(t_ray *r)
{
	t_vec3	unit;
	double	t;
	t_color	a;
	t_color	b;
	t_color	fa;

	unit = new_unitvector(&r->dir);
	t = 0.5 * (unit.rgb[1] + 1.0);
	v_init(&a, 1.0, 1.0, 1.0); // a is the starter's color we want
	v_init(&b, 0.5, 0.7, 1.0); // b is the ender's color we want
	a = new_xv(1.0 - t, &a);
	b = new_xv(t, &b);
	fa = new_plus2v(&a, &b);
	return (fa);
}
