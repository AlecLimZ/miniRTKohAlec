#include "miniRT.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX(a, b) ((a) < (b)? (b) : (a))
#define MIN(a, b) ((a) > (b)? (b) : (a))

typedef struct s_xyz {
	float x, y, z;
	// float& operator[](const int i)       { return i==0 ? x : (1==i ? y : z); }
	// const float& operator[](const int i) const { return i==0 ? x : (1==i ? y : z); }
	// vec3  operator*(const float v) const { return {x*v, y*v, z*v};       }
	// float operator*(const vec3& v) const { return x*v.x + y*v.y + z*v.z; }
	// vec3  operator+(const vec3& v) const { return {x+v.x, y+v.y, z+v.z}; }
	// vec3  operator-(const vec3& v) const { return {x-v.x, y-v.y, z-v.z}; }
	// vec3  operator-()              const { return {-x, -y, -z};          }
	// float norm() const { return sqrt(x*x+y*y+z*z); }
	// vec3 normalized() const { return (*this)*(1.f/norm(*this)); }
} vec3;

typedef struct s_Material {
	float refractive_index;
	float albedo[4]; //diffuse, specular, reflect, refract
	vec3 diffuse_color;
	float specular_exponent;
	// float refractive_index = 1;
	// float albedo[4] = {2,0,0,0};
	// vec3 diffuse_color = {0,0,0};
	// float specular_exponent = 0;
} Material;

//  #define      IVORY {1.0, {0.9,  0.5, 0.1, 0.0}, {0.4, 0.4, 0.3},   50.}
 #define      IVORY {1.0, {0.9,  0.5, 0.1, 0.0}, {0.4, 0.4, 0.3},   50.}
 #define RED_RUBBER {1.0, {1.4,  0.3, 0.0, 0.0}, {0.3, 0.1, 0.1},   10.}
 #define      GLASS {1.5, {0.0,  0.9, 0.1, 0.8}, {0.6, 0.7, 0.8},  125.}
 #define     MIRROR {1.0, {0.0, 16.0, 0.8, 0.0}, {1.0, 1.0, 1.0}, 1425.}

typedef struct s_Sphere {
	vec3 center;
	float radius;
	Material material;
} Sphere;

typedef struct s_Plane {
	vec3 diffuse_color;
	vec3 alternate_color;
} Plane;

typedef struct s_Light {
	vec3	coor;
	vec3	color;
} Light;

typedef struct s_obj {
	int type;
	union
	{
		Sphere sp;
		Plane pl;
	};
} Obj;

vec3    vadd(vec3 a, vec3 b)
{
	return (vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}

vec3    vsub(vec3 a, vec3 b)
{
	return (vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

float    mulvv(vec3 a, vec3 b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

vec3    mulvf(vec3 a, float b)
{
	return (vec3){a.x * b, a.y * b, a.z * b};
}

vec3    negate(vec3 v)
{
	return (vec3){-v.x, -v.y, -v.z};
}

float norm(vec3 v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

vec3 normalized(vec3 v)
{
	return mulvf(v, 1.f/norm(v));
}

vec3 cross(const vec3 v1, const vec3 v2) {
	return (vec3){ v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x };
}

vec3	vmul(vec3 a, vec3 b)
{
	return (vec3){a.x * b.x, a.y * b.y, a.z * b.z};
}

typedef struct s_hitpayload {
	bool hit;
	float nearest_dist;
	vec3 point;
	vec3 N;
	Material material;
} hitpayload;

//  Sphere spheres[] = {
//     {{0, -1, -10}, .1, RED_RUBBER},
//     {{-3,    0,   -16}, 2, IVORY},
//     {{-1.0, -1.5, -12}, 2, RED_RUBBER},
//     {{ 1.5, -0.5, -18}, 3, RED_RUBBER},
//     {{ 7,    5,   -18}, 4, IVORY}
// };

Obj all_objects[100] = {
	{.type = PLANE, .pl = {{.3,.3,.3}, {.3,.2,.1} }},
	{.type = SPHERE, .sp = {{0, -1, -10}, .1, RED_RUBBER}},
	{.type = SPHERE, .sp = {{-3,    0,   -16}, 2, IVORY}},
	{.type = SPHERE, .sp = {{-1.0, -1.5, -12}, 2, RED_RUBBER}},
	{.type = SPHERE, .sp = {{ 1.5, -0.5, -18}, 3, RED_RUBBER}},
	{.type = SPHERE, .sp = {{ 7,    5,   -18}, 4, IVORY}}
};

size_t obj_count = 6; //pls manual, do not auto count!! sizeof(all_objects) / sizeof(*all_objects);

 Light _lights[] = {
	{{ 30, 50, -25}, {1,1,1}},
	{{-20, 20,  20}, {1,1,1}},
	{{ 30, 20,  30}, {1,1,1}},
};

size_t light_count = sizeof(_lights) / sizeof(*_lights);

vec3 g_background = (vec3){0.2, 0.7, 0.8};

static vec3 reflect(const vec3 I, const vec3 N) {
	return vsub(I, mulvf(N,2.f*mulvv(I, N)));
}

// vec3 refract(const vec3 I, const vec3 N, const float eta_t, const float eta_i) { // Snell's law
//     float cosi = - MAX(-1.f, MIN(1.f, mulvv(I, N)));
//     if (cosi<0) return refract(I, negate(N), eta_i, eta_t); // if the ray comes from the inside the object, swap the air and the media
//     float eta = eta_i / eta_t;
//     float k = 1 - eta*eta*(1 - cosi*cosi);
//     return k<0 ? (vec3){1,0,0} : vadd(mulvf(I,eta), mulvf(N, eta*cosi - sqrt(k))); // k<0 = total reflection, no ray to refract. I refract it anyways, this has no physical meaning
// }

static float ray_sphere_intersect(const vec3 orig, const vec3 dir, const Sphere s)
{
	const vec3 L = vsub(s.center, orig);
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

static void nearest_sphere(const vec3 orig, const vec3 dir, const Obj *obj, hitpayload *payload) // ret value is a pair [intersection found, distance]
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
static void nearest_plane(const vec3 orig, const vec3 dir, const Obj *obj, hitpayload *payload)
{
	const Plane plane = obj->pl;
	 if (fabs(dir.y)>.001) { // intersect the ray with the checkerboard, avoid division by zero
	 	// this is hardcode y = -4. need to support coordiate and orientation
		const float d = -(orig.y+1.5)/dir.y; // the checkerboard plane has equation y = -4 // wonder if replacing this line is enuf for origin + orient
		const vec3 p = vadd(orig, mulvf(dir,d));
		if (d>.001 && d<payload->nearest_dist
		// && fabs(p.x)<10 && p.z<-10 && p.z>-30 // this is the size (faster), minirt is unlimited (slow)
		)
		{
			payload->nearest_dist = d;
			payload->point = p;
			payload->N = (vec3){0,1,0};
			// payload->
			 payload->material.diffuse_color = 
			// below is checker box
			// ((int)(.5*p.x+1000) + (int)(.5*p.z)) & 1 ?  // this formulate the checker box size 
			((int)(p.x+1e9) + (int)(p.z + 1e9)) & 1 ?  // this formulate the checker box size 
			// (vec3){.3, .3, .3} :  (vec3){.3, .2, .1}; //alternate color in the checker box
			obj->pl.diffuse_color: obj->pl.alternate_color;
		}
	}
}

static hitpayload scene_intersect(const vec3 orig, const vec3 dir, const Obj *objs, int count) {
	// here is restructure the code, next to add cylinder intersect function ( i have no idea at the moment)
	void (* const f[])() = {
		[SPHERE] = nearest_sphere,
		[PLANE] = nearest_plane,
	};
	// hitpayload payload = {0, 1e10, {0,0,0}, {0,0,0}, {1, {2,0,0,0}, {0,0,0}, 0}};
	hitpayload payload = {0, 1e10, {0,0,0}, {0,0,0}, {1, {1,0,0,0}, {0,0,0}, 0}};
	// vec3 pt, N;
	// Material material = {1, {2,0,0,0}, {0,0,0}, 0};
	// float nearest_dist = 1e10;

	while (count && objs)
	{
		f[objs->type](orig, dir, objs, &payload);
		--count;
		++objs;
	}
	payload.hit = payload.nearest_dist < 1000;
	return payload;

	// if (fabs(dir.y)>.001) { // intersect the ray with the checkerboard, avoid division by zero
	//     const float d = -(orig.y+4)/dir.y; // the checkerboard plane has equation y = -4
	//     const vec3 p = vadd(orig, mulvf(dir,d));
	//     if (d>.001 && d<nearest_dist && fabs(p.x)<10 && p.z<-10 && p.z>-30) {
	//         nearest_dist = d;
	//         pt = p;
	//         N = (vec3){0,1,0};
	//         material.diffuse_color = ((int)(.5*pt.x+1000) + (int)(.5*pt.z)) & 1 ? (vec3){.3, .3, .3} : (vec3){.3, .2, .1};
	//     }
	// }

	// for (size_t i =0; i < sphere_count; ++i) { // intersect the ray with all spheres
	//     const Sphere s = spheres[i];
	//     const float d = ray_sphere_intersect(orig, dir, s);
	//     if (d > nearest_dist) continue;
	//     nearest_dist = d;
	//     pt = vadd(orig, mulvf(dir,nearest_dist));
	//     N = normalized(vsub(pt, s.center));
	//     material = s.material;
	// }
	// return (hitpayload){ nearest_dist<1000, pt, N, material };
}

int _mode = 0;
// the ray tracer getting final color per pixel
static vec3 cast_ray(const vec3 orig, const vec3 dir, const int depth, const Obj *objs, const int obj_count) {
	// auto [hit, point, N, material] 
	hitpayload a = scene_intersect(orig, dir, objs, obj_count);
	if (depth>4 || !a.hit)
		return g_background; // background color

if (_mode == BY_NORMAL) return mulvf(vadd(a.N, (vec3){1,1,1}), 0.5);
// if (_mode == BY_NORMAL) return mulvf(vadd(a.N, a.material.diffuse_color), 0.5);

	const vec3 reflect_dir = normalized(reflect(dir, a.N));
	const vec3 reflect_color = cast_ray(a.point, reflect_dir, depth + 1, objs, obj_count);

	// vec3 diffuse_light_itensity_by_color = {1,1,1};

	// i expect the ambient customization around this.
	// this is the light source codes
	vec3 intensity = g_background;
	float diffuse_light_intensity = 0;  // this is the light intensity. for bonus colored light, will have to use vec3 instead of single float
	float specular_light_intensity = 0;  // this is the spark(the white-spot) effect for bonus
	for (size_t i =0; i < light_count; ++i) { // checking if the point lies in the shadow of the light
		const Light light = _lights[i];
		vec3 light_dir = normalized(vsub(light.coor, a.point));
		// auto [hit, shadow_pt, trashnrm, trashmat] 
		hitpayload b = scene_intersect(a.point, light_dir, objs, obj_count);
		if (b.hit && norm(vsub(b.point, a.point)) < norm(vsub(light.coor, a.point))) continue;
		diffuse_light_intensity  += MAX(0.f, mulvv(light_dir,a.N));
		intensity = vadd(intensity, mulvf(light.color, MAX(0.f, mulvv(light_dir,a.N))));
		specular_light_intensity += pow(MAX(0.f, mulvv(negate(reflect(negate(light_dir), a.N)),dir)), a.material.specular_exponent);
	}


	// vec3 c = (vec3) {
	// 	a.material.diffuse_color.x * diffuse_light_itensity_by_color.x * diffuse_light_intensity *  a.material.albedo[0],
	// 	a.material.diffuse_color.y * diffuse_light_itensity_by_color.y * diffuse_light_intensity *  a.material.albedo[0],
	// 	a.material.diffuse_color.z * diffuse_light_itensity_by_color.z * diffuse_light_intensity *  a.material.albedo[0],
	// };
	vec3 c =
	vadd(
		vadd(
			// mulvf(a.material.diffuse_color, diffuse_light_intensity * a.material.albedo[0]), //object color with intensity/light
			vmul(a.material.diffuse_color, intensity),
			mulvf((vec3){1., 1., 1.},specular_light_intensity * a.material.albedo[1]) //spark/white-spot effect
		),
			mulvf(reflect_color,a.material.albedo[2]) // reflection 
	);
	return c;
	// refraction removed, this is for transparent eg glass. is not needed by subject, to skip processing
	// const vec3 refract_dir = normalized(refract(dir, a.N, a.material.refractive_index, 1.f));
	// const vec3 refract_color = cast_ray(a.point, refract_dir, depth + 1, objs, obj_count);
	// c = vadd(c, mulvf(refract_color,a.material.albedo[3]));
	// return vadd(c, (vec3){ c.x * g_background.x, c.y * g_background.y, c.z * g_background.z});
	// return material.diffuse_color * diffuse_light_intensity * material.albedo[0] + vec3{1., 1., 1.}*specular_light_intensity * material.albedo[1] + reflect_color*material.albedo[2] + refract_color*material.albedo[3];
}

static int to_rgb(vec3 color)
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
			dst->sp.center = (vec3) {obj->coor.x, obj->coor.y, obj->coor.z};
			dst->sp.radius = obj->diameter / 2;
			dst->sp.material = (Material)IVORY;
			dst->sp.material.diffuse_color = (vec3) {obj->color.x, obj->color.y, obj->color.z};
		}
		else if (obj->type == PLANE)
		{
			++obj_count;
			dst = all_objects + obj_count - 1;
			dst->type = obj->type;
			dst->pl.diffuse_color = (vec3) {obj->color.x, obj->color.y, obj->color.z};
			dst->pl.alternate_color = (vec3) {obj->color.x, obj->color.y, obj->color.z};
		}
		else if (obj->type == LIGHT || obj->type == LIGHT_BONUS)
		{
			++light_count;
			_lights[light_count - 1].coor = (vec3) { obj->coor.x, obj->coor.y, obj->coor.z};
			_lights[light_count - 1].color = (vec3) {
				obj->color.x * obj->light_brightness,
				obj->color.y * obj->light_brightness,
				obj->color.z * obj->light_brightness
			};

		}
		node = node->next;
	}
	g_background = (vec3) {
		app->ambient->color.x * app->ambient->ambient_ratio,
		app->ambient->color.y * app->ambient->ambient_ratio,
		app->ambient->color.z * app->ambient->ambient_ratio
	};
	return (1);
}

void	*rt2(const t_app *app)
{
	// static int run_once = 0; //set 1 to disable rt file
	// if (!run_once) run_once = 
		load_rt_objects(app);
	_mode = app->render_mode;

	 const int   width  = app->width;
	 const int   height = app->height;
	 const vec3  camera = (vec3){app->camera->coor.x, app->camera->coor.y, app->camera->coor.z};
	 float fov    = 1.05; // 60 degrees field of view in radians  it is there already,just to replace by .rt i will do
// #pragma omp parallel for
	for (int pix = 0; pix<width*height; pix++) { // actual rendering loop
		float dir_x =  (pix%width + 0.5) -  width/2.;
		float dir_y = -(pix/width + 0.5) + height/2.; // this flips the image at the same time
		float dir_z = -height/(2.*tan(fov/2.));
rotate_x(&dir_y, &dir_z, app->camera->orientation.x);
rotate_y(&dir_x, &dir_z, app->camera->orientation.y);
rotate_z(&dir_x, &dir_y, app->camera->orientation.z);
		app->image.px[pix] = to_rgb( 
			cast_ray(camera, normalized((vec3){dir_x, dir_y, dir_z}), 0, all_objects, obj_count)
		);
	}
	return app->image.ptr;
}