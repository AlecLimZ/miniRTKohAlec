#include "miniRT.h"

#define SHELL_SCRIPT \
    gcc "$0" -O3; \
    time ./a.out > out.ppm; \
    echo saved as out.ppm; \
    exit
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX(a, b) ((a) < (b)? (b) : (a))
#define MIN(a, b) ((a) > (b)? (b) : (a))

// typedef t_vec3 vec3;
typedef struct s_xyz {
    float x, y, z;
    //       float& operator[](const int i)       { return i==0 ? x : (1==i ? y : z); }
    // const float& operator[](const int i) const { return i==0 ? x : (1==i ? y : z); }
    // vec3  operator*(const float v) const { return {x*v, y*v, z*v};       }
    // float operator*(const vec3& v) const { return x*v.x + y*v.y + z*v.z; }
    // vec3  operator+(const vec3& v) const { return {x+v.x, y+v.y, z+v.z}; }
    // vec3  operator-(const vec3& v) const { return {x-v.x, y-v.y, z-v.z}; }
    // vec3  operator-()              const { return {-x, -y, -z};          }
    // float norm() const { return sqrt(x*x+y*y+z*z); }
    // vec3 normalized() const { return (*this)*(1.f/norm(*this)); }
} vec3;



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

typedef struct s_Material {
    float refractive_index;
    float albedo[4];
    vec3 diffuse_color;
    float specular_exponent;
    // float refractive_index = 1;
    // float albedo[4] = {2,0,0,0};
    // vec3 diffuse_color = {0,0,0};
    // float specular_exponent = 0;
} Material;

typedef struct s_hitpayload {
    bool hit;
    vec3 point;
    vec3 N;
    Material material;
} hitpayload;

typedef struct s_Sphere {
    vec3 center;
    float radius;
    Material material;
} Sphere;

 #define      IVORY {1.0, {0.9,  0.5, 0.1, 0.0}, {0.4, 0.4, 0.3},   50.}
 #define      GLASS {1.5, {0.0,  0.9, 0.1, 0.8}, {0.6, 0.7, 0.8},  125.}
 #define RED_RUBBER {1.0, {1.4,  0.3, 0.0, 0.0}, {0.3, 0.1, 0.1},   10.}
 #define     MIRROR {1.0, {0.0, 16.0, 0.8, 0.0}, {1.0, 1.0, 1.0}, 1425.}

 Sphere spheres[] = {
    {{0, -1, -10}, .1, RED_RUBBER},
    {{-3,    0,   -16}, 2, IVORY},
    {{-1.0, -1.5, -12}, 2, RED_RUBBER},
    {{ 1.5, -0.5, -18}, 3, RED_RUBBER},
    {{ 7,    5,   -18}, 4, IVORY}
};
const size_t sphere_count = sizeof(spheres) / sizeof(*spheres);

 vec3 lights[] = {
    {-20, 20,  20},
    { 30, 50, -25},
    { 30, 20,  30}
};

vec3 reflect(const vec3 I, const vec3 N) {
    return vsub(I, mulvf(N,2.f*mulvv(I, N)));
}

vec3 refract(const vec3 I, const vec3 N, const float eta_t, const float eta_i) { // Snell's law
    float cosi = - MAX(-1.f, MIN(1.f, mulvv(I, N)));
    if (cosi<0) return refract(I, negate(N), eta_i, eta_t); // if the ray comes from the inside the object, swap the air and the media
    float eta = eta_i / eta_t;
    float k = 1 - eta*eta*(1 - cosi*cosi);
    return k<0 ? (vec3){1,0,0} : vadd(mulvf(I,eta), mulvf(N, eta*cosi - sqrt(k))); // k<0 = total reflection, no ray to refract. I refract it anyways, this has no physical meaning
}

float ray_sphere_intersect(const vec3 orig, const vec3 dir, const Sphere s) { // ret value is a pair [intersection found, distance]
    const vec3 L = vsub(s.center, orig);
    const float tca = mulvv(L,dir);
    const float d2 = mulvv(L,L) - tca*tca;
    if (d2 > s.radius*s.radius) return INFINITY;
    const float thc = sqrt(s.radius*s.radius - d2);
    const float t0 = tca-thc, t1 = tca+thc;
    if (t0>.001) return t0;  // offset the original point by .001 to avoid occlusion by the object itself
    if (t1>.001) return t1;
    return INFINITY;
}

hitpayload scene_intersect(const vec3 orig, const vec3 dir) {
    vec3 pt, N;
    Material material = {1, {2,0,0,0}, {0,0,0}, 0};

    float nearest_dist = 1e10;
    if (fabs(dir.y)>.001) { // intersect the ray with the checkerboard, avoid division by zero
        float d = -(orig.y+4)/dir.y; // the checkerboard plane has equation y = -4
        vec3 p = vadd(orig, mulvf(dir,d));
        if (d>.001 && d<nearest_dist && fabs(p.x)<10 && p.z<-10 && p.z>-30) {
            nearest_dist = d;
            pt = p;
            N = (vec3){0,1,0};
            material.diffuse_color = ((int)(.5*pt.x+1000) + (int)(.5*pt.z)) & 1 ? (vec3){.3, .3, .3} : (vec3){.3, .2, .1};
        }
    }

    for (size_t i =0; i < sphere_count; ++i) { // intersect the ray with all spheres
        const Sphere s = spheres[i];
        float d = ray_sphere_intersect(orig, dir, s);
        if (d > nearest_dist) continue;
        nearest_dist = d;
        pt = vadd(orig, mulvf(dir,nearest_dist));
        N = normalized(vsub(pt, s.center));
        material = s.material;
    }
    return (hitpayload){ nearest_dist<1000, pt, N, material };
}

vec3 cast_ray(const vec3 orig, const vec3 dir, const int depth) {
    // auto [hit, point, N, material] 
    hitpayload a = scene_intersect(orig, dir);
    if (depth>4 || !a.hit)
        // return (vec3){0., 0., 0.}; // background color
        return (vec3){0.2, 0.7, 0.8}; // background color

    const vec3 reflect_dir = normalized(reflect(dir, a.N));
    // const vec3 refract_dir = normalized(refract(dir, a.N, a.material.refractive_index, 1.f));
    const vec3 reflect_color = cast_ray(a.point, reflect_dir, depth + 1);
    // const vec3 refract_color = cast_ray(a.point, refract_dir, depth + 1);

    float diffuse_light_intensity = 0, specular_light_intensity = 0;
    for (int i =0; i < 3; ++i) { // checking if the point lies in the shadow of the light
        const vec3 light = lights[i];
        vec3 light_dir = normalized(vsub(light, a.point));
        // auto [hit, shadow_pt, trashnrm, trashmat] 
        hitpayload b = scene_intersect(a.point, light_dir);
        if (b.hit && norm(vsub(b.point, a.point)) < norm(vsub(light, a.point))) continue;
        diffuse_light_intensity  += MAX(0.f, mulvv(light_dir,a.N));
        specular_light_intensity += pow(MAX(0.f, mulvv(negate(reflect(negate(light_dir), a.N)),dir)), a.material.specular_exponent);
    }
    return 
    vadd(
        // vadd(
            vadd(
                mulvf(a.material.diffuse_color, diffuse_light_intensity * a.material.albedo[0]),
                mulvf((vec3){1., 1., 1.},specular_light_intensity * a.material.albedo[1])
            ) , mulvf(reflect_color,a.material.albedo[2])
        // ), mulvf(refract_color,a.material.albedo[3])
    );
    // return material.diffuse_color * diffuse_light_intensity * material.albedo[0] + vec3{1., 1., 1.}*specular_light_intensity * material.albedo[1] + reflect_color*material.albedo[2] + refract_color*material.albedo[3];
}

int xmain() {
     int   width  = 1024;
     int   height = 768;
     float fov    = 1.05; // 60 degrees field of view in radians
    vec3 *framebuffer = (vec3*)malloc(sizeof(vec3) * width*height);
// #pragma omp parallel for
    for (int pix = 0; pix<width*height; pix++) { // actual rendering loop
        float dir_x =  (pix%width + 0.5) -  width/2.;
        float dir_y = -(pix/width + 0.5) + height/2.; // this flips the image at the same time
        float dir_z = -height/(2.*tan(fov/2.));
        framebuffer[pix] = cast_ray((vec3){0,0,0}, normalized((vec3){dir_x, dir_y, dir_z}), 0);
    }

    // std::ofstream ofs("./out.ppm", std::ios::binary);
    printf("P6\n%d %d\n255\n", width, height);
    // ofs << "P6\n" << width << " " << height << "\n255\n";
    for (vec3 *color = framebuffer; color < framebuffer + width*height; ++color) {
        float max = MAX(1.f, MAX(color->x, MAX(color->y, color->z)));
            // ofs << (char)(255 *  color->x/max);
            // ofs << (char)(255 *  color->y/max);
            // ofs << (char)(255 *  color->z/max);
        printf("%c%c%c", (char)(255 *  color->x/max), (char)(255 *  color->y/max), (char)(255 *  color->z/max));
    }
    free(framebuffer);
    return 0;
}

int to_rgb(vec3 color)
{
    const float max = MAX(1.f, MAX(color.x, MAX(color.y, color.z)));
    return (
        ((int)(255 *  color.x/max) << 16 )
        +  ((int)(255 *  color.y/max) << 8)
        +  (int)(255 *  color.z/max)
        );
}

void	*rt2(const t_app *app)
{

     const int   width  = app->width;
     const int   height = app->height;
     const vec3  camera = (vec3){app->camera.origin.x, app->camera.origin.y, app->camera.origin.z};
     float fov    = 1.05; // 60 degrees field of view in radians
    // vec3 *framebuffer = (vec3*)malloc(sizeof(vec3) * width*height);
// #pragma omp parallel for
    for (int pix = 0; pix<width*height; pix++) { // actual rendering loop
        float dir_x =  (pix%width + 0.5) -  width/2.;
        float dir_y = -(pix/width + 0.5) + height/2.; // this flips the image at the same time
        float dir_z = -height/(2.*tan(fov/2.));
        // framebuffer[pix] = 
        app->image.px[pix] = to_rgb( 
        cast_ray(camera, normalized((vec3){dir_x, dir_y, dir_z}), 0)
        );
    }
    return app->image.ptr;
}