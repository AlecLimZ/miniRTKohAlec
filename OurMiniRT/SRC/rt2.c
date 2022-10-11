#include "miniRT.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX(a, b) ((a) < (b)? (b) : (a))
#define MIN(a, b) ((a) > (b)? (b) : (a))

typedef struct s_Material {
	float refractive_index;
	float albedo[4]; //diffuse, specular, reflect, refract
	t_vec3 diffuse_color;
	float specular_exponent;
} Material;

//  #define      IVORY {1.0, {0.9,  0.5, 0.1, 0.0}, {0.4, 0.4, 0.3},   50.}
 #define      IVORY {1.0, {0.9,  0.5, 0.1, 0.0}, {{0.4, 0.4, 0.3}},   50.}
 #define RED_RUBBER {1.0, {1.4,  0.3, 0.0, 0.0}, {{0.3, 0.1, 0.1}},   10.}
 #define      GLASS {1.5, {0.0,  0.9, 0.1, 0.8}, {{0.6, 0.7, 0.8}},  125.}
 #define     MIRROR {1.0, {0.0, 16.0, 0.8, 0.0}, {{1.0, 1.0, 1.0}}, 1425.}

typedef struct s_Sphere {
	t_vec3 center;
	float radius;
	Material material;
} Sphere;

typedef struct s_Plane {
	t_vec3 diffuse_color;
	t_vec3 alternate_color;
} Plane;

typedef struct s_Light {
	t_vec3	coor;
	t_vec3	color;
} Light;

typedef struct s_obj {
	int type;
	union
	{
		Sphere sp;
		Plane pl;
	};
} Obj;

t_vec3    vadd(t_vec3 a, t_vec3 b)
{
	return (t_vec3){{a.x + b.x, a.y + b.y, a.z + b.z}};
}

t_vec3    vsub(t_vec3 a, t_vec3 b)
{
	return (t_vec3){{a.x - b.x, a.y - b.y, a.z - b.z}};
}

float    mulvv(t_vec3 a, t_vec3 b)
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

typedef struct s_hitpayload {
	bool hit;
	float nearest_dist;
	t_vec3 point;
	t_vec3 N;
	Material material;
} hitpayload;

Obj all_objects[100] = {
	{.type = PLANE, .pl = {{{.3,.3,.3}}, {{.3,.2,.1}} }},
	{.type = SPHERE, .sp = {{{0, -1, -10}}, .1, RED_RUBBER}},
	{.type = SPHERE, .sp = {{{-3,    0,   -16}}, 2, IVORY}},
	{.type = SPHERE, .sp = {{{-1.0, -1.5, -12}}, 2, RED_RUBBER}},
	{.type = SPHERE, .sp = {{{ 1.5, -0.5, -18}}, 3, RED_RUBBER}},
	{.type = SPHERE, .sp = {{{ 7,    5,   -18}}, 4, IVORY}}
};

size_t obj_count = 6; //pls manual, do not auto count!! sizeof(all_objects) / sizeof(*all_objects);

 Light _lights[] = {
	{{{ 30, 50, -25}}, {{1,1,1}}},
	{{{-20, 20,  20}}, {{1,1,1}}},
	{{{ 30, 20,  30}}, {{1,1,1}}},
};

size_t light_count = sizeof(_lights) / sizeof(*_lights);

t_vec3 g_background = (t_vec3){{0.2, 0.7, 0.8}};

static t_vec3 reflect(const t_vec3 I, const t_vec3 N) {
	return vsub(I, mulvf(N,2.f*mulvv(I, N)));
}


static float ray_sphere_intersect(const t_vec3 orig, const t_vec3 dir, const Sphere s)
{
	const t_vec3 L = vsub(s.center, orig);
	const float tca = mulvv(L,dir); // => L * dir
	const float d2 = mulvv(L,L) - tca*tca;

	if (d2 > s.radius*s.radius) return INFINITY; // within the sphere range
	const float thc = sqrt(s.radius*s.radius - d2);
	const float t0 = tca-thc;
	const float t1 = tca+thc;
	// the 2 hit points
	if (t0>.001) return t0;  // offset the original point by .001 to avoid occlusion by the object itself
	if (t1>.001) return t1;
	return INFINITY;
}

static void nearest_sphere(const t_vec3 orig, const t_vec3 dir, const Obj *obj, hitpayload *payload) // ret value is a pair [intersection found, distance]
{
	const Sphere s = obj->sp;
	const float d = ray_sphere_intersect(orig, dir, s);
	if (d <= payload->nearest_dist)
	{
		payload->nearest_dist = d;
		payload->point = vadd(orig, mulvf(dir,payload->nearest_dist));
		payload->N = normalized(vsub(payload->point, s.center));
		payload->material = s.material;
	}
}

// this is the plane intersect
// yes plane is object and can have many planes.
static void nearest_plane(const t_vec3 orig, const t_vec3 dir, const Obj *obj, hitpayload *payload)
{
	const Plane plane = obj->pl;
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
			// payload->
			 payload->material.diffuse_color = 
			// below is checker box
			// ((int)(.5*p.x+1000) + (int)(.5*p.z)) & 1 ?  // this formulate the checker box size 
			((int)(p.x+1e9) + (int)(p.z + 1e9)) & 1 ?  // this formulate the checker box size 
			// (t_vec3){.3, .3, .3} :  (t_vec3){.3, .2, .1}; //alternate color in the checker box
			obj->pl.diffuse_color: obj->pl.alternate_color;
		}
	}
}

static hitpayload scene_intersect(const t_vec3 orig, const t_vec3 dir, const Obj *objs, int count) {
	// here is restructure the code, next to add cylinder intersect function ( i have no idea at the moment)
	void (* const f[])() = {
		[SPHERE] = nearest_sphere,
		[PLANE] = nearest_plane,
	};
	hitpayload payload = {0, 1e10, {{0,0,0}}, {{0,0,0}}, {1, {1,0,0,0}, {{0,0,0}}, 0}};

	while (count && objs)
	{
		f[objs->type](orig, dir, objs, &payload);
		--count;
		++objs;
	}
	payload.hit = payload.nearest_dist < 1000;
	return payload;
}

int _mode = 0;
// the ray tracer getting final color per pixel
static t_vec3 cast_ray(const t_vec3 orig, const t_vec3 dir, const int depth, const Obj *objs, const int obj_count) {
	hitpayload a = scene_intersect(orig, dir, objs, obj_count);
	if (depth>4 || !a.hit)
		return g_background; // background color
	if (_mode == BY_NORMAL) return mulvf(vadd(a.N, (t_vec3){{1,1,1}}), 0.5);

	const t_vec3 reflect_dir = normalized(reflect(dir, a.N));
	const t_vec3 reflect_color = cast_ray(a.point, reflect_dir, depth + 1, objs, obj_count);

	// i expect the ambient customization around this.
	// this is the light source codes
	t_vec3 intensity = g_background;
	float diffuse_light_intensity = 0;  // this is the light intensity. for bonus colored light, will have to use t_vec3 instead of single float
	float specular_light_intensity = 0;  // this is the spark(the white-spot) effect for bonus
	for (size_t i =0; i < light_count; ++i) { // checking if the point lies in the shadow of the light
		const Light light = _lights[i];
		t_vec3 light_dir = normalized(vsub(light.coor, a.point));
		hitpayload b = scene_intersect(a.point, light_dir, objs, obj_count);
		if (b.hit && norm(vsub(b.point, a.point)) < norm(vsub(light.coor, a.point))) continue;
		diffuse_light_intensity  += MAX(0.f, mulvv(light_dir,a.N));
		intensity = vadd(intensity, mulvf(light.color, MAX(0.f, mulvv(light_dir,a.N))));
		specular_light_intensity += pow(MAX(0.f, mulvv(negate(reflect(negate(light_dir), a.N)),dir)), a.material.specular_exponent);
	}
	return vadd(
		vadd(
			vmul(a.material.diffuse_color, intensity),
			mulvf((t_vec3){{1., 1., 1.}},specular_light_intensity * a.material.albedo[1]) //spark/white-spot effect
		),
		mulvf(reflect_color,a.material.albedo[2]) // reflection 
	);
}

static int to_rgb(t_vec3 color)
{
	const float max = MAX(1.f, MAX(color.x, MAX(color.y, color.z)));
	return (
		((int)(255 *  color.x/max) << 16 )
		+  ((int)(255 *  color.y/max) << 8)
		+  (int)(255 *  color.z/max)
		);
}

// temporary code i customize tinyraytracer data to use .rt file
static int load_rt_objects(const t_app *app)
{
	t_object *obj;
	Obj *dst;
	obj_count = 0;
	light_count = 0;
	t_list *node = app->objects;
	while (node)
	{
		obj = node->content;
		if (obj->type == SPHERE)
		{
			++obj_count;
			dst = all_objects + obj_count - 1;
			dst->type = obj->type;
			dst->sp.center = (t_vec3) {{obj->coor.x, obj->coor.y, obj->coor.z}};
			dst->sp.radius = obj->diameter / 2;
			dst->sp.material = (Material)IVORY;
			dst->sp.material.diffuse_color = (t_vec3) {{obj->color.x, obj->color.y, obj->color.z}};
		}
		else if (obj->type == PLANE)
		{
			++obj_count;
			dst = all_objects + obj_count - 1;
			dst->type = obj->type;
			dst->pl.diffuse_color = (t_vec3) {{obj->color.x, obj->color.y, obj->color.z}};
			dst->pl.alternate_color = (t_vec3) {{obj->color.x, obj->color.y, obj->color.z}};
		}
		else if (obj->type == LIGHT || obj->type == LIGHT_BONUS)
		{
			++light_count;
			_lights[light_count - 1].coor = (t_vec3) {{ obj->coor.x, obj->coor.y, obj->coor.z}};
			_lights[light_count - 1].color = (t_vec3) {{
				obj->color.x * obj->light_brightness,
				obj->color.y * obj->light_brightness,
				obj->color.z * obj->light_brightness
			}};

		}
		node = node->next;
	}
	g_background = (t_vec3) {{
		app->ambient->color.x * app->ambient->ambient_ratio,
		app->ambient->color.y * app->ambient->ambient_ratio,
		app->ambient->color.z * app->ambient->ambient_ratio
	}};
	return (1);
}

void	*rt2(const t_app *app)
{
	load_rt_objects(app);
	_mode = app->render_mode;

	 const int   width  = app->width;
	 const int   height = app->height;
	 const t_vec3  camera = (t_vec3){{app->camera->coor.x, app->camera->coor.y, app->camera->coor.z}};
	 const float fov    = app->camera->camera_fov * PI /180 ; // 1.05 = 60 degrees field of view in radians  it is there already,just to replace by .rt i will do
// #pragma omp parallel for
	for (int pix = 0; pix<width*height; ++pix) { // actual rendering loop
		float dir_x =  (pix%width + 0.5) -  width/2.;
		float dir_y = -(pix/width + 0.5) + height/2.; // this flips the image at the same time
		float dir_z = -height/(2.*tan(fov/2.));
rotate_x(&dir_y, &dir_z, app->camera->orientation.x);
rotate_y(&dir_x, &dir_z, app->camera->orientation.y);
rotate_z(&dir_x, &dir_y, app->camera->orientation.z);
		app->image.px[pix] = to_rgb( 
			cast_ray(camera, normalized((t_vec3){{dir_x, dir_y, dir_z}}), 0, all_objects, obj_count)
		);
	}
	return app->image.ptr;
}
