#include "miniRT.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX(a, b) ((a) < (b)? (b) : (a))
#define MIN(a, b) ((a) > (b)? (b) : (a))

int g_mode = DEFAULT_RENDER;
t_vec3 g_background = (t_vec3){{255, 255, 255}};

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


static float ray_cylinder_intersect(t_vec3 orig, t_vec3 dir, const t_object *cy, t_vec3 *normal)
{
//	float a = (dir.x * dir.x) + (dir.z * dir.z);
//	float b = 2 * (dir.x * (orig.x - cy->coor.x) + dir.z * (orig.z - cy->coor.z));
//	float c = (orig.x - cy->coor.x) * (orig.x - cy->coor.x) + (orig.z - cy->coor.z) * (orig.z - cy->coor.z) - (cy->radius * cy->radius);
//	here norm version is dot version...

	// try https://stackoverflow.com/questions/65566282/cylinder-intersection-with-ray-tracing
//	t_vec3	nori;
//	t_vec3	ndir;
//	t_vec3	len;
//	t_vec3	nrot;

//	nori = ray->orig;
//	nrot = normalized(cy->orientation);
//	ndir = cross(ray->dir, nrot);
//	len = vsub(ray->orig, cy->coor);

//	t_vec3 tmp = cross(len, nrot);
//	double a = ft_dot(&ndir, &ndir);
//	double b = 2 * ft_dot(&ndir, &tmp);
//	double c = ft_dot(&tmp, &tmp)
//		- (cy->radius / 2) * (cy->radius / 2);

//	float delta = b * b - 4 * a * c;
//	if (delta < 0)
//		ray->hit = 0;

//	float t1 = (-b - sqrt(delta)) / (2 * a);
//	float t2 = (-b + sqrt(delta)) / (2 * a);
//	if (t2 < 0)
//		ray->hit = 0;
//	if (t1 > 0)
//		ray->t = t1;
//	else
//		ray->t = t2;

//	if (norm(vsub(ray->norm, cy->coor)) > cy->height)
//		ray->hit = 0;
//	tmp = vsub(ray->norm, cy->coor);
//	double ax = ft_dot(&nrot, &tmp);
//	tmp = mulvf(nrot, ax);
//	tmp = vadd(cy->coor, tmp);
//	ray->norm = normalized(vsub(ray->norm, tmp));
//	ray->hit = 1;
//	ray->t = ax;
//
//	sphere testing
//	t_vec3 oc = vsub(orig, cy->coor);
//	float	b = mulvv(oc, dir);
//	float	c = mulvv(oc, oc) - cy->radius * cy->radius;
//	float	h = b * b - c;
//	if (h < 0.0)
//		return INFINITY;
//	h = sqrt(h);
//	float t0 = -b-h;
//	float t1 = -b+h;
//	if (t0 > .001) return t0;
//	if (t1 > .001) return t1;
//	return INFINITY;
	//cy->coor is the coordination center of the cylinder right?
	//just need to understand ur object coorA
	// vec3 ba is height
	// vec3 oc is 
	// if we decide coor as point A, we can add height to the point A to get point B vector right?
	t_vec3 pa = cy->coor;
	t_vec3 pb = (t_vec3){{cy->coor.x, fabs(cy->coor.y - cy->height), cy->coor.z}};
//	printf("height: %f\n", cy->height);
//	printf("height: %f\n", pb.y);
//	exit(0);
	t_vec3 ca = vsub(pb, pa);
	t_vec3 oc = vsub(orig, pa);

	float caca = mulvv(ca, ca);
	float card = mulvv(ca, dir);
	float caoc = mulvv(ca, orig);

	float a = caca - card * card;
	float b = caca * mulvv(oc, dir) - caoc * card;
	float c = caca * mulvv(oc, oc) - caoc * caoc - cy->radius * cy->radius * caca;
	float h = b * b - a * c;

	if (h < 0.001)
		return INFINITY;
	h = sqrt(h);
	float d = (-b-h)/a;

	// body
	float y = caoc + d * card;
	if (y > 0. && y < caca)
	{
		*normal = mulvf(ca, y);
		*normal = new_dividev(normal, caca);
		*normal = vsub(vadd(oc, mulvf(dir, d)), *normal);
		*normal = new_dividev(normal, cy->radius);
		return d;
	}

	// caps circle
	d = ((y < 0. ? 0. : caca) - caoc) / card;
	if (fabs(b + a * d) < h)
	{
		y = (y > 0) ? 1 : ((y < 0) ? -1 : 0);
		*normal =	mulvf(ca, y);
	   *normal = normalized(new_dividev(normal, caca));
//	   *normal = new_dividev(normal, caca);
	   return (d);
	}
	return INFINITY;
}

static void nearest_cylinder(const t_vec3 orig, const t_vec3 dir, const t_object *cy, hitpayload *payload)
{
	t_vec3	normal;
	float d = ray_cylinder_intersect(orig, dir, cy, &normal);
	if (d < payload->nearest_dist && d > 0.001)
	{
		payload->nearest_dist = d;
		payload->point = normal;
	//	payload->N = normalized(payload->point); // no shadow on top
		payload->N = normalized(vsub(payload->point, cy->coor));
		//payload->N = normalized(vsub(payload->point, s->coor));
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
static t_vec3 cast_ray(const t_vec3 orig, const t_vec3 dir, const int depth, t_list *list)
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
