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

// this is the plane intersect
// yes plane is object and can have many planes.
// void nearest_plane(const t_vec3 orig, const t_vec3 dir, 
// const t_object *plane, t_hitpayload *payload)
// {
// intersect the ray with the checkerboard, avoid division by zero
// 	 if (fabs(dir.y)>.001) {
// 	 	// this is hardcode y = -4. need to support coordiate and orientation
// the checkerboard plane has equation y = -4
// 		const float d = -(orig.y+1.5)/dir.y; 
// 		const t_vec3 p = vadd(orig, mulvf(dir,d));
// 		if (d>.001 && d<payload->nearest_dist
// 		// && fabs(p.x)<10 && p.z<-10 && p.z>-30
// 		)
// 		{
// 			payload->nearest_dist = d;
// 			payload->point = p;
// 			payload->normal = (t_vec3){{0,1,0}};
// 			payload->material.diffuse_color = //plane->color;
// 			// below is checker box
// 			 //*
// 			// ((int)(.5*p.x+1000) + (int)(.5*p.z)) & 1 ? 
// 			// ((int)(p.x+1e9) + (int)(p.z + 1e9)) & 1 ? 
// 			(abs((int)(p.x)) + abs((int)(p.z))) % 2 ? 
// 			// (t_vec3){.3, .3, .3} :  (t_vec3){.3, .2, .1};
// 			plane->color: vsub(plane->color, (t_vec3){{.1,.1,.1}});
// 			//*/
// 		}
// 	}
// }

void	nearest_plane3(const t_vec3 orig, const t_vec3 dir,
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
	}
}
// void	nearest_plane2( t_vec3 orig, const t_vec3 dir, 
// const t_object *plane, t_hitpayload *payload)
// {
// 	// -(dot(ro, p.xyz) + 1.0) / dot(rd, p.xyz);
// 	orig = vsub(orig, plane->coor);
// 	const float t = 
// - (mulvv(orig, plane->orientation) + 1.0) / mulvv(dir,plane->orientation);
// 	if (t > .001 && t < payload->nearest_dist)
// 	{
// 		payload->nearest_dist = t;
// 		payload->point = vadd(orig, mulvf(dir, t));
// 		payload->normal = plane->orientation;
// 		payload->material.diffuse_color = plane->color; 
// 	}
// }
