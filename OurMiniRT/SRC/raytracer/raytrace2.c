/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:19:34 by Koh               #+#    #+#             */
/*   Updated: 2022/10/19 18:20:03 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>
#include "raytracer.h"

static t_vec3	reflect(const t_vec3 i, const t_vec3 normal) {
	return (vsub(i, mulvf(normal, 2.f * mulvv(i, normal))));
}

static t_hitpayload	scene_intersect(
	const t_vec3 orig, const t_vec3 dir, const t_list *list)
{
	t_hitpayload payload;
		
	payload = (t_hitpayload)
		{0, 1e10, {{0,0,0}}, {{0,0,0}}, {{1,0,0}, 0, {{0,0,0}}}};
	while (list)
	{
		if (as_object(list)->type == SPHERE)
			nearest_sphere(orig, dir, list->content, &payload);
		else if (as_object(list)->type == PLANE)
			nearest_plane3(orig, dir, list->content, &payload);
		else if (((t_object *)list->content)->type == CYLINDER)
			nearest_cylinder(orig, dir, list->content, &payload);
		list = list->next;
	}
	payload.hit = payload.nearest_dist < 1000;
	return (payload);
}


static t_vec3	sum_color(t_hitpayload a, t_vec3 reflect_color,
	t_vec3 diffuse_light_intensity, float specular_light_intensity)
{
	return (vadd(
		vadd(
			vmul(a.material.diffuse_color, diffuse_light_intensity),
			mulvf((t_vec3){{1., 1., 1.}},
				specular_light_intensity * a.material.albedo[1])
		),
		mulvf(reflect_color,a.material.albedo[2])
	));
}

// if (g_mode == BY_DISTANCE)
//	return mulvf((t_vec3) {{1,1,1}}, (fmax(0,16- a.nearest_dist))/16);
// if (g_mode == BY_NORMAL)
//	return mulvf(vadd(a.normal, (t_vec3){{1,1,1}}), 0.5);
// if (g_mode == BY_OBJECT) return a.material.diffuse_color;
// the ray tracer getting final color per pixel
t_vec3	cast_ray(const t_vec3 orig, t_vec3 dir,
	const int depth, t_list *list, t_rgb bg)
{
	const t_list	    *lights = list;
	const t_hitpayload  a = scene_intersect(orig, dir, list);

	if (depth > 4 || !a.hit)
		return (bg);
	const t_vec3 reflect_dir = normalized(reflect(dir, a.normal));
	const t_vec3 reflect_color = cast_ray(a.point, reflect_dir, depth + 1, list, bg);
	float specular_light_intensity = 0;
	t_vec3 diffuse_light_intensity = bg;
	while (lights)
	{
		if (as_object(lights)->type == LIGHT || as_object(lights)->type == LIGHT_BONUS)
		{
			const t_object *light = lights->content;
			t_vec3 light_dir = normalized(vsub(light->coor, a.point));
			t_hitpayload b = scene_intersect(a.point, light_dir, list);
			if (!(b.hit && norm(vsub(b.point, a.point)) < norm(vsub(light->coor, a.point))))
			{
				diffuse_light_intensity = vadd(diffuse_light_intensity, mulvf(light->light_color, fmax(0.f, mulvv(light_dir,a.normal))));
				specular_light_intensity += pow(fmax(0.f, mulvv(negate(reflect(negate(light_dir), a.normal)),dir)), a.material.specular_exponent);
			}
		}
		lights = lights->next;
	}
	return (sum_color(a, reflect_color, 
		diffuse_light_intensity, specular_light_intensity));
}
