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

static void	set_checkerboard(const t_object *plane, t_hitpayload *payload)
{
	if (((int)(payload->point.x) + (int)(payload->point.z)
		+ (payload->point.x < 0) + (payload->point.z < 0)) & 1)
		payload->material.diffuse_color = mulvf(plane->color, .9);
}

void	nearest_plane(const t_vec3 orig, const t_vec3 dir,
	const t_object *plane, t_hitpayload *payload)
{
	float		distance;
	const float	denom = mulvv(dir, plane->orientation);

	if (fabs(denom) < 0.001)
		return ;
	distance = mulvv(vsub(plane->coor, orig), plane->orientation) / denom;
	if (payload->nearest_dist > distance && distance > 0.001)
	{
		payload->nearest_dist = distance;
		payload->point = vadd(orig, mulvf(dir, distance));
		payload->material = plane->material;
		payload->object = plane;
		if (denom > 0)
			payload->normal = negate(plane->orientation);
		else
			payload->normal = plane->orientation;
		if (plane->checkerboard_enabled)
			set_checkerboard(plane, payload);
	}
}
