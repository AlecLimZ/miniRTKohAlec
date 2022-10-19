/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <leng-chu@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 14:44:43 by leng-chu          #+#    #+#             */
/*   Updated: 2022/09/17 14:45:13 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "raytrace.h"

static void	quadratic(float a, float b, float c, float *res)
{
	float	sqrt_discriminant;
	float	aux[2];

	sqrt_discriminant = sqrt(pow(b, 2) - 4 * a * c);
	aux[0] = (-b - sqrt_discriminant) / (2 * a);
	aux[1] = (-b + sqrt_discriminant) / (2 * a);
	if (aux[0] < aux[1])
	{
		res[0] = aux[0];
		res[1] = aux[1];
	}
	else
	{
		res[0] = aux[1];
		res[1] = aux[0];
	}
}

static float	ray_cylinder_intersect(t_ray *r,
		const t_object *cy, bool ret[2])
{
	t_vec3	p[2];
	t_vec3	cyry;
	float	t[2];
	float	dist[2];

	p[0] = vsub(r->dir, mulvf(r->norm, mulvv(r->dir, r->norm)));
	p[1] = vsub(vsub(r->orig, cy->coor),
			mulvf(r->norm, mulvv(vsub(r->orig, cy->coor), r->norm)));
	quadratic(vlenf(p[0]), 2 * mulvv(p[0], p[1]),
		vlenf(p[1]) - pow(cy->radius, 2), t);
	cyry = vsub(cy->coor, r->orig);
	dist[0] = mulvv(r->norm, vsub(mulvf(r->dir, t[0]), cyry));
	dist[1] = mulvv(r->norm, vsub(mulvf(r->dir, t[1]), cyry));
	ret[0] = (dist[0] >= 0 && dist[0] <= cy->height && t[0] > 0.001);
	ret[1] = (dist[1] >= 0 && dist[1] <= cy->height && t[1] > 0.001);
	if (ret[0] == false && ret[1] == true)
	{
		r->y = dist[1];
		return (t[1]);
	}
	r->y = dist[0];
	return (t[0]);
}

void	nearest_cylinder(const t_vec3 orig, t_vec3 dir,
		const t_object *cy, t_hitpayload *payload)
{
	t_ray	r;
	bool	ret[2];
	float	d;

	r.orig = orig;
	r.dir = dir;
	r.norm = normalized(cy->orientation);
	d = ray_cylinder_intersect(&r, cy, ret);
	if ((ret[0] || ret[1]) && payload->nearest_dist > d && d > 0.001)
	{
		payload->nearest_dist = d;
		payload->point = vadd(orig, mulvf(dir, payload->nearest_dist));
		if (ret[0] == false && ret[1] == true)
			payload->normal = mulvf(payload->normal, -1);
		else
			payload->normal = normalized(vsub(payload->point,
						vadd(mulvf(r.norm, r.y), cy->coor)));
		payload->material = cy->material;
	}
}
