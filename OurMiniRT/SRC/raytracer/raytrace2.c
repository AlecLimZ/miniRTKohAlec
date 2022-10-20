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

//t_vec3 diffuse_light_intensity, float specular_light_intensity
static t_vec3	cast_reflect_ray(t_vec3 dir, t_hitpayload a, const int depth,
	const t_app *app)
{
	const t_vec3 reflect_dir = normalized(reflect(dir, a.normal));
	const t_vec3 reflect_color = cast_ray(a.point, reflect_dir, depth, app);

	return (mulvf(reflect_color, a.material.albedo[2]));
}

static void	cast_shadow_ray(t_light_trace *rt, const t_object *light, 
	t_hitpayload a, const t_app *app)
{
	const t_vec3		light_dir = normalized(vsub(light->coor, a.point));
	const t_hitpayload	obstacle = scene_intersect(a.point, light_dir, app->objects);

	if (!(obstacle.hit && norm(vsub(obstacle.point, a.point)) < norm(vsub(light->coor, a.point))))
	{
		rt->diffuse_light_intensity = vadd(rt->diffuse_light_intensity, 
			mulvf(light->light_color, fmax(0.f, mulvv(light_dir, a.normal))));
		if (app->features & FEATURE_SPECULAR)
			rt->specular_light_intensity += pow(
				fmax(0.f, mulvv(negate(reflect(negate(light_dir), a.normal)), rt->dir)),
				a.material.specular_exponent);
	}
}

// if (g_mode == BY_DISTANCE)
//	return mulvf((t_vec3) {{1,1,1}}, (fmax(0,16- a.nearest_dist))/16);

// find closest object and distance
// get its material
// with hitpoint and light source, find diffuse_light_intensity (gradient)
//		and specular_light_intensity (optional)
// (optional) with hitpoint and hitpoint normal, find reflection[albedo]
// pixel = (material * (ambient + diffuse_light_intensity)) 
//		+ (white * specular_light_intensity[exponent,albedo])
//		+ reflection
t_vec3	cast_ray(const t_vec3 orig, t_vec3 dir,
	const int depth, const t_app *app)
{
	const t_hitpayload 	a = scene_intersect(orig, dir, app->objects);
	const t_list	    *lights = app->objects;
	t_light_trace		rt;
	t_vec3				color;

	if (depth > 4 || !a.hit)
		return (app->object[AMBIENT]->light_color);
	if (app->features & FEATURE_NORMAL)
		return mulvf(vadd(a.normal, (t_vec3){{1, 1, 1}}), 0.5);
	if ((app->features & FEATURE_LIGHT) == 0)
		return (a.material.diffuse_color);
	rt.dir = dir;
	rt.specular_light_intensity = 0;
	rt.diffuse_light_intensity = app->object[AMBIENT]->light_color;
	while (lights)
	{
		if (as_object(lights)->type == LIGHT || as_object(lights)->type == LIGHT_BONUS)
			cast_shadow_ray(&rt, lights->content, a, app);
		lights = lights->next;
	}
	color = vadd(vmul(a.material.diffuse_color, rt.diffuse_light_intensity),
			mulvf((t_vec3){{1., 1., 1.}}, rt.specular_light_intensity * a.material.albedo[1]));
	if (app->features & FEATURE_REFLECTION)
		return (vadd(color, cast_reflect_ray(dir, a, depth + 1, app)));
	return (color);
}
