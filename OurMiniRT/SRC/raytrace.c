/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:19:34 by Koh               #+#    #+#             */
/*   Updated: 2022/10/19 19:04:56 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// float fmax(float a, float b)
// {
// 	if (a < b)
// 		return (b);
// 	else
// 		return (a);
// }

int g_mode = DEFAULT_RENDER;
t_vec3 g_background = (t_vec3){{0, 0, 0}};

t_object	*as_object(const t_list *p)
{
	return (p->content);
}

typedef struct s_hitpayload {
	bool hit;
	float nearest_dist;
	t_vec3 point;
	t_vec3 N;
	t_material material;
} hitpayload;

t_vec3	vadd(t_vec3 a, t_vec3 b)
{
	return (t_vec3){{a.x + b.x, a.y + b.y, a.z + b.z}};
}

t_vec3	vsub(t_vec3 a, t_vec3 b)
{
	return (t_vec3){{a.x - b.x, a.y - b.y, a.z - b.z}};
}

float    mulvv(t_vec3 a, t_vec3 b) // same as dot
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

t_vec3	mulvf(t_vec3 a, float b)
{
	return (t_vec3){{a.x * b, a.y * b, a.z * b}};
}

t_vec3	negate(t_vec3 v)
{
	return (t_vec3){{-v.x, -v.y, -v.z}};
}

float norm(t_vec3 v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

t_vec3 normalized(t_vec3 v)
{
	return mulvf(v, 1.f/norm(v));
}

// t_vec3 cross(const t_vec3 v1, const t_vec3 v2) {
// 	return (t_vec3){{ v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x }};
// }

t_vec3	vmul(t_vec3 a, t_vec3 b)
{
	return (t_vec3){{a.x * b.x, a.y * b.y, a.z * b.z}};
}

static t_vec3 reflect(const t_vec3 I, const t_vec3 N) {
	return vsub(I, mulvf(N,2.f*mulvv(I, N)));
}

float	vlenf(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

// float	clamp(float value, float lo, float hi)
// {
// 	if (value < lo)
// 		return (lo);
// 	if (value > hi)
// 		return (hi);
// 	return (value);
// }

// float smootherstep(float edge0, float edge1, float x) {
//   // Scale, and clamp x to 0..1 range
//   x = clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0);
//   // Evaluate polynomial
//   return x * x * x * (x * (x * 6 - 15) + 10);
// }

static float ray_sphere_intersect(const t_vec3 orig, const t_vec3 dir, const t_object *s)
{
	const t_vec3 L = vsub(s->coor, orig);
	const float tca = mulvv(L,dir); // => L * dir
	const float d2 = mulvv(L,L) - tca*tca;

	if (d2 > s->radius*s->radius) return INFINITY;
	const float thc = sqrt(s->radius*s->radius - d2);
	const float t0 = tca-thc;
	const float t1 = tca+thc;
	if (t0>.001) return t0;  // offset the original point by .001 to avoid occlusion by the object itself
	if (t1>.001) return t1;
	return INFINITY;
}

static void nearest_sphere(const t_vec3 orig, const t_vec3 dir, const t_object *s, hitpayload *payload) // ret value is a pair [intersection found, distance]
{
	const float d = ray_sphere_intersect(orig, dir, s);
	if (d <= payload->nearest_dist)
	{
		payload->nearest_dist = d;
		payload->point = vadd(orig, mulvf(dir,payload->nearest_dist));
		payload->N = normalized(vsub(payload->point, s->coor));
		payload->material = s->material;
	}
}

//	bool hit;
//	float nearest_dist;
//	t_vec3 point;
//	t_vec3 N;
//	t_material material;

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

static void	nearest_cylinder(const t_vec3 orig, t_vec3 dir,
		const t_object *cy, hitpayload *payload)
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
			payload->N = mulvf(payload->N, -1);
		else
			payload->N = normalized(vsub(payload->point,
						vadd(mulvf(r.norm, r.y), cy->coor)));
		payload->material = cy->material;
	}
}

// this is the plane intersect
// yes plane is object and can have many planes.
static void nearest_plane(const t_vec3 orig, const t_vec3 dir, const t_object *plane, hitpayload *payload)
{
	 if (fabs(dir.y)>.001) { // intersect the ray with the checkerboard, avoid division by zero
	 	// this is hardcode y = -4. need to support coordiate and orientation
		const float d = -(orig.y+1.5)/dir.y; // the checkerboard plane has equation y = -4 // wonder if replacing this line is enuf for origin + orient
		const t_vec3 p = vadd(orig, mulvf(dir,d));
		if (d>.001 && d<payload->nearest_dist
		// && fabs(p.x)<10 && p.z<-10 && p.z>-30
		)
		{
			payload->nearest_dist = d;
			payload->point = p;
			payload->N = (t_vec3){{0,1,0}};
			payload->material.diffuse_color = //plane->color;
			// below is checker box
			 //*
			// ((int)(.5*p.x+1000) + (int)(.5*p.z)) & 1 ?  // this formulate the checker box size 
			// ((int)(p.x+1e9) + (int)(p.z + 1e9)) & 1 ?  // this formulate the checker box size 
			(abs((int)(p.x)) + abs((int)(p.z))) % 2 ?  // this formulate the checker box size 
			// (t_vec3){.3, .3, .3} :  (t_vec3){.3, .2, .1}; //alternate color in the checker box
			plane->color: vsub(plane->color, (t_vec3){{.1,.1,.1}});
			//*/
		}
	}
}

static void nearest_plane2(const t_vec3 orig, const t_vec3 dir, const t_object *plane, hitpayload *payload)
{
	const float	denom = mulvv(plane->orientation, dir);
	if (fabs(denom) > .001 )
	{
		const t_vec3 p0l0 = vsub(plane->coor, orig);
		const float	distance = mulvv(p0l0, plane->orientation) / denom;
		if (distance > .001 && distance < payload->nearest_dist)
		{
			payload->nearest_dist = distance;
			payload->point = vadd(orig, mulvf(dir, distance));
			const t_vec3 nn = negate(plane->orientation);
			if (vlenf(vsub(orig, vadd(payload->point, nn))) <
			 vlenf(vsub(orig, vadd(payload->point, plane->orientation))))
				payload->N = nn;
			else
				payload->N = plane->orientation;
			payload->material.diffuse_color = plane->color; 
		}
	}
}

static void nearest_plane3(const t_vec3 orig, const t_vec3 dir, t_object *plane, hitpayload *payload)
{
	// noted that plane->orientation is normalized
	float	den;
	float	d;

	den = mulvv(normalized(dir), plane->orientation);
	if (!den)
		d = INFINITY;
	d = mulvv(vsub(plane->coor, orig), plane->orientation) / den;
	if (payload->nearest_dist > d && d > 0.001)
	{
		payload->nearest_dist = d;
		payload->point = vadd(orig, mulvf(dir, payload->nearest_dist));
		if (mulvv(dir, plane->orientation) > 0)
			plane->orientation = mulvf(plane->orientation, -1);
		payload->N = plane->orientation;
		payload->material = plane->material;
		//payload->material.diffuse_color = plane->color; 
	}
}
// void	nearest_plane2( t_vec3 orig, const t_vec3 dir, const t_object *plane, hitpayload *payload)
// {
// 	// -(dot(ro, p.xyz) + 1.0) / dot(rd, p.xyz);
// 	orig = vsub(orig, plane->coor);
// 	const float t = - (mulvv(orig, plane->orientation) + 1.0) / mulvv(dir,plane->orientation);
// 	if (t > .001 && t < payload->nearest_dist)
// 	{
// 		payload->nearest_dist = t;
// 		payload->point = vadd(orig, mulvf(dir, t));
// 		payload->N = plane->orientation;
// 		payload->material.diffuse_color = plane->color; 
// 	}
// }

static hitpayload scene_intersect(const t_vec3 orig, const t_vec3 dir, const t_list *list)
{
	hitpayload payload = {0, 1e10, {{0,0,0}}, {{0,0,0}}, {{1,0,0}, 0, {{0,0,0}}}};

	while (list)
	{
		if (as_object(list)->type == SPHERE)
			nearest_sphere(orig, dir, list->content, &payload);
		else if (as_object(list)->type == PLANE)
			//nearest_plane2(orig, dir, list->content, &payload);
			nearest_plane3(orig, dir, list->content, &payload);
		else if (((t_object *)list->content)->type == CYLINDER)
			nearest_cylinder(orig, dir, list->content, &payload);
		if (0)
			nearest_plane(orig, dir, list->content, &payload);
		if (0)
			nearest_plane2(orig, dir, list->content, &payload);
		list = list->next;
	}
	payload.hit = payload.nearest_dist < 1000;
	return payload;
}

// the ray tracer getting final color per pixel
static t_vec3 cast_ray(const t_vec3 orig, t_vec3 dir, const int depth, t_list *list)
{
	const t_list	*lights = list;
	const hitpayload a = scene_intersect(orig, dir, list);
	if (depth>4 || !a.hit)
		return g_background; // background color
	if (g_mode == BY_DISTANCE) return mulvf((t_vec3) {{1,1,1}}, (fmax(0,16- a.nearest_dist))/16);
	if (g_mode == BY_NORMAL) return mulvf(vadd(a.N, (t_vec3){{1,1,1}}), 0.5);
	if (g_mode == BY_OBJECT) return a.material.diffuse_color;

	const t_vec3 reflect_dir = normalized(reflect(dir, a.N));
	const t_vec3 reflect_color = cast_ray(a.point, reflect_dir, depth + 1, list);

	// todo specular with colored light
	float specular_light_intensity = 0;  // this is the spark(the white-spot) effect for bonus
	t_vec3 diffuse_light_intensity = g_background;
	// checking if the point lies in the shadow of the light
	while (lights)
	{
		if (as_object(lights)->type == LIGHT || as_object(lights)->type == LIGHT_BONUS)
		{
			const t_object *light = lights->content;
			t_vec3 light_dir = normalized(vsub(light->coor, a.point));
			hitpayload b = scene_intersect(a.point, light_dir, list);
			if (!(b.hit && norm(vsub(b.point, a.point)) < norm(vsub(light->coor, a.point))))
			{
				diffuse_light_intensity = vadd(diffuse_light_intensity, mulvf(light->light_color, fmax(0.f, mulvv(light_dir,a.N))));
				specular_light_intensity += pow(fmax(0.f, mulvv(negate(reflect(negate(light_dir), a.N)),dir)), a.material.specular_exponent);
			}
		}
		lights = lights->next;
	}
	return vadd(
		vadd(
			vmul(a.material.diffuse_color, diffuse_light_intensity),
			mulvf((t_vec3){{1., 1., 1.}},specular_light_intensity * a.material.albedo[1]) //spark/white-spot effect
		),
		mulvf(reflect_color,a.material.albedo[2]) // reflection 
	);
}

// gamma correction 1/2.2 == 0.4545
static int to_rgb(t_vec3 color, bool use_gamma_correction)
{
	float	max;

	if (use_gamma_correction)
	{
		color.x = pow(color.x, 0.4545);
		color.y = pow(color.y, 0.4545);
		color.z = pow(color.z, 0.4545);
	}
	max = fmax(1.f, fmax(color.x, fmax(color.y, color.z)));

	return (((int)(255.999 *  color.x/max) << 16 )
		+  ((int)(255.999 *  color.y/max) << 8)
		+  (int)(255.999 *  color.z/max));
}

static void	update_lights(t_list *objects)
{
	t_object	*o;

	while (objects)
	{
		o = as_object(objects);
		if (o->type == AMBIENT || o->type == LIGHT || o->type == LIGHT_BONUS)
		{
			o->light_color.r = o->param1 * o->color.r;
			o->light_color.g = o->param1 * o->color.g;
			o->light_color.b = o->param1 * o->color.b;
		}
		objects = objects->next;
	}
}

void	*raytrace(const t_app *app)
{
	update_lights(app->objects);
	g_background = app->object_ptr[AMBIENT]->light_color;
	g_mode = app->render_mode;
	
	const int   width  = app->image.width;
	const int   height = app->image.height;
	const float fov	= app->object_ptr[CAMERA]->camera_fov * PI /180 ; // 1.05 = 60 degrees field of view in radians  it is there already,just to replace by .rt i will do
	for (int pix = 0; pix<width*height; ++pix)
	{ // actual rendering loop
		float dir_x =  (pix%width + 0.5) -  width/2.;
		float dir_y = -(pix/width + 0.5) + height/2.; // this flips the image at the same time
		float dir_z = -height/(2.*tan(fov/2.));
rotate_x(&dir_y, &dir_z, app->object_ptr[CAMERA]->orientation.x);
rotate_y(&dir_x, &dir_z, app->object_ptr[CAMERA]->orientation.y);
rotate_z(&dir_x, &dir_y, app->object_ptr[CAMERA]->orientation.z);
		app->image.px[pix] = to_rgb( 
			cast_ray(app->object_ptr[CAMERA]->coor, normalized((t_vec3){{dir_x, dir_y, dir_z}}), 0, app->objects),
			app->use_gamma_correction
		);
	}
	return app->image.ptr;
}
