/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 23:12:51 by Koh               #+#    #+#             */
/*   Updated: 2022/10/11 23:16:33 by Koh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

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
	const float	d = ray_sphere_intersect(orig, dir, s);

	if (d <= payload->nearest_dist)
	{
		payload->nearest_dist = d;
		payload->point = vadd(orig, mulvf(dir, payload->nearest_dist));
		payload->normal = normalized(vsub(payload->point, s->coor));
		payload->material = s->material;
	}
}
