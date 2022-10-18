#include "miniRT.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX(a, b) ((a) < (b)? (b) : (a))
#define MIN(a, b) ((a) > (b)? (b) : (a))

int g_mode = DEFAULT_RENDER;
t_vec3 g_background = (t_vec3){{0, 0, 0}};

typedef struct s_hitpayload {
	bool hit;
	float nearest_dist;
	t_vec3 point;
	t_vec3 N;
	t_material material;
} hitpayload;

t_vec3    vadd(t_vec3 a, t_vec3 b)
{
	return (t_vec3){{a.x + b.x, a.y + b.y, a.z + b.z}};
}

t_vec3    vsub(t_vec3 a, t_vec3 b)
{
	return (t_vec3){{a.x - b.x, a.y - b.y, a.z - b.z}};
}

float    mulvv(t_vec3 a, t_vec3 b) // same as dot
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

t_vec3    mulvf(t_vec3 a, float b)
{
	return (t_vec3){{a.x * b, a.y * b, a.z * b}};
}

t_vec3    negate(t_vec3 v)
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

t_vec3 cross(const t_vec3 v1, const t_vec3 v2) {
	return (t_vec3){{ v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x }};
}

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

static float ray_cylinder_intersect(t_vec3 orig, t_vec3 dir, const t_object *cy, t_vec3 *normal, float *y, bool ret[2])
{
	// try https://stackoverflow.com/questions/65566282/cylinder-intersection-with-ray-tracing
//rotate_x(&dir_y, &dir_z, app->camera->orientation.x);
//rotate_y(&dir_x, &dir_z, app->camera->orientation.y);
//rotate_z(&dir_x, &dir_y, app->camera->orientation.z);
//	t_vec3 pa = cy->coor;
//	t_vec3 pb = (t_vec3){{cy->coor.x, fabs(cy->coor.y + cy->height), cy->coor.z}};
//	t_vec3 ca = vsub(pb, pa);
//	t_vec3 oc = vsub(orig, pa);
//
//	float caca = mulvv(ca, ca);
//	float card = mulvv(ca, dir);
//	float caoc = mulvv(ca, orig);
//
//	float a = caca - card * card;
//	float b = caca * mulvv(oc, dir) - caoc * card;
//	float c = caca * mulvv(oc, oc) - caoc * caoc - cy->radius * cy->radius * caca;
//	float h = b * b - a * c;
//
//	if (h < 0.001)
//		return INFINITY;
//	h = sqrt(h);
//	float d = (-b-h)/a;
//
//	// body
//	float y = caoc + d * card;
//	if (y > 0. && y < caca)
//	{
//		*normal = mulvf(ca, y);
//		*normal = new_dividev(normal, caca);
//		*normal = vsub(vadd(oc, mulvf(dir, d)), *normal);
//		*normal = new_dividev(normal, cy->radius);
//		return d;
//	}
//
//	// caps circle
//	d = ((y < 0. ? 0. : caca) - caoc) / card;
//	if (fabs(b + a * d) < h)
//	{
//		y = (y > 0) ? 1 : ((y < 0) ? -1 : 0);
//		*normal =	mulvf(ca, y);
//		*normal = normalized(new_dividev(normal, caca));
////	   *normal = new_dividev(normal, caca);
//	   return (d);
//	}
	t_vec3 v[2];
	t_vec3 v_cy2ray;
	float time[2];
	float dist[2];

	// cy->orientation is normalized at parser_types.c
	v[0] = vsub(dir, mulvf(cy->orientation, mulvv(dir, cy->orientation)));
	v[1] = vsub(vsub(orig, cy->coor), mulvf(cy->orientation, mulvv(vsub(orig, cy->coor), cy->orientation)));
	quadratic(vlenf(v[0]), 2 * mulvv(v[0], v[1]), vlenf(v[1]) - pow(cy->radius / 2, 2), time);
	v_cy2ray = vsub(cy->coor, orig);
	dist[0] = mulvv(cy->orientation, vsub(mulvf(dir, time[0]), v_cy2ray));
	dist[1] = mulvv(cy->orientation, vsub(mulvf(dir, time[1]), v_cy2ray));
	ret[0] = (dist[0] >= 0 && dist[0] <= cy->height && time[0] > 0.001);
	ret[1] = (dist[1] >= 0 && dist[1] <= cy->height && time[1] > 0.001);
	if (ret[0] == false && ret[1] == true)
	{
		*y = dist[1];
		return (time[1]);
	}
	*y = dist[0];

	// caps circle
	t_vec3 pa = cy->coor;
	t_vec3 pb = (t_vec3){{cy->coor.x, fabs(cy->coor.y + cy->height), cy->coor.z}};
	t_vec3 ca = vsub(pb, pa);
	t_vec3 oc = vsub(orig, pa);
	float caca = mulvv(ca, ca);
	float card = mulvv(ca, dir);
	float caoc = mulvv(ca, orig);
	float a = caca - card * card;
	float b = caca * mulvv(oc, dir) - caoc * card;
	float c = caca * mulvv(oc, oc) - caoc * caoc - cy->radius * cy->radius * caca;
	float h = b * b - a * c;
	h = sqrt(h);
	float d = (-b-h) / a;
	float yy = caoc + d * card;
	d = ((yy < 0. ? 0. : caca) - caoc) / card;
	if (fabs(b + a * d) < h)
	{
		yy = (yy > 0) ? 1 : ((yy < 0) ? -1 : 0);
		*normal = mulvf(ca, yy);
		*normal = normalized(new_dividev(normal, caca));
		*normal = new_dividev(normal, caca);
		return (d);
	}

	// default correct
	return (time[0]);
}

static void nearest_cylinder(const t_vec3 orig, t_vec3 dir, const t_object *cy, hitpayload *payload)
{
	t_vec3	normal;
	bool ret[2];
	float y;
//	rotate_dx(&dir.y, &dir.z, cy->orientation.x);
//	rotate_dy(&dir.x, &dir.z, cy->orientation.y);
//	rotate_dz(&dir.x, &dir.y, cy->orientation.z);
	float d = ray_cylinder_intersect(orig, dir, cy, &normal, &y, ret);
	if ((ret[0] || ret[1]) && payload->nearest_dist > d && d > 0.001)
	{
		payload->nearest_dist = d;
		payload->point = vadd(orig, mulvf(dir,payload->nearest_dist));
		if (ret[0] == false && ret[1] == true)
			payload->N = mulvf(payload->N, -1);
		else
			payload->N = normalized(vsub(payload->point, vadd(mulvf(cy->orientation, y), cy->coor)));
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
		// && fabs(p.x)<10 && p.z<-10 && p.z>-30 // this is the size (faster), minirt is unlimited (slow)
		)
		{
			payload->nearest_dist = d;
			payload->point = p;
			payload->N = (t_vec3){{0,1,0}};
			payload->material.diffuse_color = plane->color;
			// below is checker box
			 /*
			// ((int)(.5*p.x+1000) + (int)(.5*p.z)) & 1 ?  // this formulate the checker box size 
			((int)(p.x+1e9) + (int)(p.z + 1e9)) & 1 ?  // this formulate the checker box size 
			// (t_vec3){.3, .3, .3} :  (t_vec3){.3, .2, .1}; //alternate color in the checker box
			obj->pl.diffuse_color: obj->pl.alternate_color;
			*/
		}
	}
}

static hitpayload scene_intersect(const t_vec3 orig, const t_vec3 dir, const t_list *list)
{
	hitpayload payload = {0, 1e10, {{0,0,0}}, {{0,0,0}}, {{1,0,0}, 0, {{0,0,0}}}};

	while (list)
	{
		if (((t_object *)list->content)->type == SPHERE)
			nearest_sphere(orig, dir, list->content, &payload);
		else if (((t_object *)list->content)->type == PLANE)
			nearest_plane(orig, dir, list->content, &payload);
		else if (((t_object *)list->content)->type == CYLINDER)
			nearest_cylinder(orig, dir, list->content, &payload);
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
	if (g_mode == BY_DISTANCE) return mulvf((t_vec3) {{1,1,1}}, (MAX(0,16- a.nearest_dist))/16);
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
		if (((t_object *)lights->content)->type == LIGHT || ((t_object *)lights->content)->type == LIGHT_BONUS)
		{
			const t_object *light = lights->content;
			t_vec3 light_dir = normalized(vsub(light->coor, a.point));
			hitpayload b = scene_intersect(a.point, light_dir, list);
			if (!(b.hit && norm(vsub(b.point, a.point)) < norm(vsub(light->coor, a.point))))
			{
				diffuse_light_intensity = vadd(diffuse_light_intensity, mulvf(light->color, MAX(0.f, mulvv(light_dir,a.N))));
				specular_light_intensity += pow(MAX(0.f, mulvv(negate(reflect(negate(light_dir), a.N)),dir)), a.material.specular_exponent);
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

static int to_rgb(t_vec3 color)
{
	const float max = MAX(1.f, MAX(color.x, MAX(color.y, color.z)));

	return (((int)(255 *  color.x/max) << 16 )
		+  ((int)(255 *  color.y/max) << 8)
		+  (int)(255 *  color.z/max));
}

void	*raytrace(const t_app *app)
{
	g_background = app->ambient->color;
	g_mode = app->render_mode;
	// load_rt_objects(app);

	 const int   width  = app->width;
	 const int   height = app->height;
	 const float fov    = app->camera->camera_fov * PI /180 ; // 1.05 = 60 degrees field of view in radians  it is there already,just to replace by .rt i will do
	for (int pix = 0; pix<width*height; ++pix) { // actual rendering loop
		float dir_x =  (pix%width + 0.5) -  width/2.;
		float dir_y = -(pix/width + 0.5) + height/2.; // this flips the image at the same time
		float dir_z = -height/(2.*tan(fov/2.));
rotate_x(&dir_y, &dir_z, app->camera->orientation.x);
rotate_y(&dir_x, &dir_z, app->camera->orientation.y);
rotate_z(&dir_x, &dir_y, app->camera->orientation.z);
		app->image.px[pix] = to_rgb( 
			cast_ray(app->camera->coor, normalized((t_vec3){{dir_x, dir_y, dir_z}}), 0, app->objects)
		);
	}
	return app->image.ptr;
}
