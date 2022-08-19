/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 09:47:33 by hloke             #+#    #+#             */
/*   Updated: 2022/06/20 17:36:30 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMENT_H
# define ELEMENT_H

# include "error.h"
# include "linalg.h"
# include "image.h"

typedef struct s_obj	t_obj;	// forward declaration for object
typedef struct s_ray	t_ray;	// forward declaration for ray
typedef struct s_light	t_light;	// forward declaration for light

typedef int				(*t_intersect)(
	t_obj *obj, t_ray *ray, t_vec *point, t_vec *norm);
typedef void			(*t_coeff)(t_obj *obj, t_ray *ray, double *coeff);
typedef t_vec*			(*t_normal)(
	t_obj *obj, t_ray *ray, t_vec *point, t_vec *norm);
typedef t_vec*			(*t_colour)(t_obj *obj, t_vec *point);
typedef t_vec*			(*t_intense)(t_light *light, t_ray *ray);

/* struct representing a ray
 * @org	the point of origin. w-coordinate = 1
 * @dir	direction of the ray. w-coordinate = 0
 */
typedef struct s_ray
{
	t_vec	*org;
	t_vec	*dir;
}	t_ray;

/* struct representing a camera
 * @fov		field of view in degrees
 * @near	distance between the camera and the centre of projection
 * @lx		half horizontal size of the screen
 * @ly		half vertical sieze of the screen
 * @reso_x	horizontal resolution of the image
 * @reso_y	vetical resolution of the image
 * @to_world	transformation matrix to transform coordinates to world view
 * @fr_world	transformation matrix to transform coorditates to object view
 */
typedef struct s_cam
{
	double	fov;
	double	near;
	double	lx;
	double	ly;
	int		reso_x;
	int		reso_y;
	t_vec	*centre;
	t_mat	*rotate;
	t_mat	*to_world;
	t_mat	*fr_world;
}	t_cam;

/* struct representing a light source
 * @type	the type of light
 * @centre	4D vector representing the centre of the light
 * @dir		4D vector representing the direction of the light
 * @colour	3D vector representing the colour of the light, each element
 * 			having the range [0, 1]
 * @param	4D vector representing the parameters of the light
 *			kc	constant attenuation constant
 * 			kl	linear attenuation constant
 * 			kq	quadratic attenuation constant
 * 			p	spot light exponent
 * intense	pointer to the light intensity calculation function
 */
typedef struct s_light
{
	t_vec		*centre;
	t_vec		*dir;
	t_vec		*param;
	t_vec		*colour;
	t_intense	intense;
}	t_light;

/* struct representing an element
 * @type		the type of element
 * @dimension	array recording the dimension of the element.
 * 				for sphere: [radius]
 * @colour		array recording the colours of the element, i.e. [R, G, B]
 * @to_world	transformation matrix to transform coordinates to world view
 * @fr_world	transformation matrix to transform coorditates to object view
 */
typedef struct s_obj
{
	t_vec		*dimension;
	t_vec		*base_colour;
	t_vec		*centre;
	t_mat		*rotate;
	t_mat		*to_world;
	t_mat		*fr_world;
	t_intersect	intersect;
	t_coeff		coefficient;
	t_normal	normal;
	t_colour	colour;
	t_colour	checkerboard;
	int			disruption;
	t_img		*norm_map;
}	t_obj;

/* struct representing options to be passed during object initializsation */
typedef struct s_opt
{
	t_vec	*colour;
	int		disruption;
	char	*norm_map;
}	t_opt;

// ft_camera.c -- camera related functions
t_cam	*ft_camera_new(t_vec *ctr, t_vec *orient, double fov);
t_ray	*ft_camera_ray(t_cam *camera, int i, int j);
void	ft_camera_del(t_cam *camera);

// ft_light.c -- light related functions
t_light	*ft_light_new(t_vec *ctr, t_vec *dir, t_vec *param, t_vec *colour);
void	ft_light_del(t_light *light);

// ft_light_ambient.c -- ambient light source related functions
t_light	*ft_ambient_new(double ratio, t_vec *colour);
t_vec	*ft_ambient_intensity(t_light *light, t_ray *ray);

// ft_light_point.c -- point light related functions
t_light	*ft_point_new(t_vec *ctr, double ratio, t_vec *colour);
t_vec	*ft_point_intensity(t_light *light, t_ray *ray);

// ft_light_spot.c -- spot light related functions
t_light	*ft_spot_new(t_vec *ctr, t_vec *dir, double ratio, t_vec *colour);
t_vec	*ft_spot_intensity(t_light *light, t_ray *ray);

// ft_obj.c -- 2nd order surface object functions
t_obj	*ft_obj_new(t_vec *ctr, t_vec *orient, t_vec *dim, t_opt *opt);
void	ft_obj_del(t_obj *obj);
int		ft_obj_intersect(t_obj *obj, t_ray *ray, t_vec *point, t_vec *norm);
t_vec	*ft_correct_normal(t_vec *norm, t_ray *ray);
t_vec	*ft_obj_colour(t_obj *obj, t_vec *point);

// ft_obj_cone.c -- cone related functions
t_obj	*ft_cone_new(t_vec *ctr, t_vec *orient, double height, t_opt *opt);
void	ft_cone_coefficient(t_obj *cone, t_ray *ray, double *coeff);
t_vec	*ft_cone_norm_map(t_obj *cone, t_vec *point, t_vec *norm);
t_vec	*ft_cone_normal(t_obj *cone, t_ray *ray, t_vec *point, t_vec *norm);

// ft_obj_cylinder.c -- cylinder related functions
t_obj	*ft_cylinder_new(t_vec *ctr, t_vec *orient, t_vec *dim, t_opt *opt);
void	ft_cylinder_coefficient(t_obj *cy, t_ray *ray, double *coeff);
t_vec	*ft_cylinder_norm_map(t_obj *cy, t_vec *point, t_vec *norm);
t_vec	*ft_cylinder_normal(t_obj *cy, t_ray *ray, t_vec *point, t_vec *norm);

// ft_obj_plane.c -- plane related functions
t_obj	*ft_plane_new(t_vec *point, t_vec *norm, t_opt *opt);
int		ft_plane_intersect(t_obj *plane, t_ray *ray, t_vec *point, t_vec *norm);
t_vec	*ft_plane_normal(t_obj *plane, t_ray *ray, t_vec *point, t_vec *norm);

// ft_obj_sphere.c -- sphere related functions
t_obj	*ft_sphere_new(t_vec *ctr, t_vec *orient, t_vec *dim, t_opt *opt);
void	ft_sphere_coefficient(t_obj *sp, t_ray *ray, double *coeff);
t_vec	*ft_sphere_norm_map(t_obj *sp, t_vec *point, t_vec *norm);
t_vec	*ft_sphere_normal(t_obj *sp, t_ray *ray, t_vec *point, t_vec *norm);

// ft_obj_checkerboard.c -- checkerboard colour disruption functions
t_vec	*ft_cone_checkerboard(t_obj *cone, t_vec *point);
t_vec	*ft_cylinder_checkerboard(t_obj *cy, t_vec *point);
t_vec	*ft_plane_checkerboard(t_obj *plane, t_vec *point);
t_vec	*ft_sphere_checkerboard(t_obj *sp, t_vec *point);

// ft_obj_norm_map.c -- norm map related functions
t_img	*ft_norm_map(const char *pathname);
t_vec	*ft_bump_norm(t_vec *colour, t_vec *norm);
t_vec	*ft_plane_norm_map(t_obj *plane, t_vec *point, t_vec *norm);

// ft_ray.c -- ray related functions
t_ray	*ft_ray_new(t_vec *origin, t_vec *direction);
void	ft_ray_del(t_ray *ray);
t_ray	*ft_ray_copy(t_ray *ray);
t_ray	*ft_ray_transform(t_mat *A, t_ray *ray);
t_vec	*ft_ray_calc_point(t_ray *ray, double t, t_vec *point);

#endif
