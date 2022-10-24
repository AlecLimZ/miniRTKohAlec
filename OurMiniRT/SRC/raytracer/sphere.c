/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 23:12:51 by Koh               #+#    #+#             */
/*   Updated: 2022/10/25 07:34:33 by Koh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

static void	set_checkerboard(const t_object *s, t_hitpayload *payload)
{
	const t_vec3	p = vsub(payload->point, s->coor);
	const float		phi = acos(p.y / norm(p));
	const float		ru = atan2(p.x, p.z) / (2 * 3.14159);
	const float		u = 1 - (ru + 0.5);
	const float		v = 1 - phi / 3.14159;

	if (((int)(u * 16 * s->radius) + (int)(v * 9 * s->radius)) & 1)
		payload->material.diffuse_color
			= mulvf(payload->material.diffuse_color, .9);
}

static float	get_distance(float tca, float thc)
{
	const float	t0 = tca - thc;
	const float	t1 = tca + thc;

	if (t0 > .001)
		return (t0);
	if (t1 > .001)
		return (t1);
	return (INFINITY);
}

// offset the original point by .001 to avoid occlusion by the object itself
static float	ray_sphere_intersect(
	const t_vec3 orig, const t_vec3 dir, const t_object *s)
{
	const t_vec3	l = vsub(s->coor, orig);
	const float		tca = mulvv(l, dir);
	const float		d2 = mulvv(l, l) - tca * tca;
	float			thc;

	if (d2 > s->radius * s->radius)
		return (INFINITY);
	thc = sqrt(s->radius * s->radius - d2);
	return (get_distance(tca, thc));
}

void	nearest_sphere(const t_vec3 orig, const t_vec3 dir,
	const t_object *s, t_hitpayload *payload)
{
	const float	distance = ray_sphere_intersect(orig, dir, s);

	if (distance <= payload->nearest_dist)
	{
		payload->nearest_dist = distance;
		payload->point = vadd(orig, mulvf(dir, distance));
		payload->normal = normalized(vsub(payload->point, s->coor));
		if (mulvv(payload->normal, dir) > 0)
			payload->normal = negate(payload->normal);
		payload->material = s->material;
		payload->object = s;
		if (s->checkerboard_enabled)
			set_checkerboard(s, payload);
	}
}
