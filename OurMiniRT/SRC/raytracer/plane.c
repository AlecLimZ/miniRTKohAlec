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

// void nearest_plane2(const t_vec3 orig, const t_vec3 dir,
	// const t_object *plane, t_hitpayload *payload)
// {
// 	const float	denom = mulvv(plane->orientation, dir);
// 	if (fabs(denom) > .001 )
// 	{
// 		const t_vec3 p0l0 = vsub(plane->coor, orig);
// 		const float	distance = mulvv(p0l0, plane->orientation) / denom;
// 		if (distance > .001 && distance < payload->nearest_dist)
// 		{
// 			payload->nearest_dist = distance;
// 			payload->point = vadd(orig, mulvf(dir, distance));
// 			const t_vec3 nn = negate(plane->orientation);
// 			if (vlenf(vsub(orig, vadd(payload->point, nn))) <
// 			 vlenf(vsub(orig, vadd(payload->point, plane->orientation))))
// 				payload->normal = nn;
// 			else
// 				payload->normal = plane->orientation;
// 			payload->material.diffuse_color = plane->color; 
// 		}
// 	}
// }

void	nearest_plane3(const t_vec3 orig, const t_vec3 dir,
	const t_object *plane, t_hitpayload *payload)
{
	float	den;
	float	d;

	den = mulvv(dir, plane->orientation);
	if (!den)
		d = INFINITY;
	d = mulvv(vsub(plane->coor, orig), plane->orientation) / den;
	if (payload->nearest_dist > d && d > 0.001)
	{
		payload->nearest_dist = d;
		payload->point = vadd(orig, mulvf(dir, payload->nearest_dist));
		if (mulvv(dir, plane->orientation) > 0)
			payload->normal = mulvf(plane->orientation, -1);
		else
			payload->normal = plane->orientation;
		payload->material = plane->material;
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
