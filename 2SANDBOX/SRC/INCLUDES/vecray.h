/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecray.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:29:08 by leng-chu          #+#    #+#             */
/*   Updated: 2022/10/11 15:52:17 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECRAY_H
# define VECRAY_H

# include <math.h>

typedef union	s_vec3
{
	double	rgb[3];
	double	xyz[3];
}	t_vec3;

typedef t_vec3	t_point3;
typedef t_vec3	t_color;
typedef t_vec3	t_vec2;

typedef struct s_ray
{
	t_point3	ori;
	t_vec3		dir;
	t_vec3		norm;
	t_vec3		pthit;
}	t_ray;

typedef struct	s_material
{
	t_color	diffuse_color;
	t_vec3	albedo;
	double	specular_exponent;
}	t_material;

typedef struct s_sphere
{
	t_vec3		center;
	double		radius;
	t_material	material;
}	t_sphere;

typedef struct s_light
{
	t_vec3	position;
	double	intensity;
}	t_light;

typedef struct s_setting
{
	int			fov;
	t_ray		ray;
	t_sphere	*splist;
	t_light		*lights;
	t_color		colorout;
}	t_setting;

double		ft_squared_len(const t_vec3 *v);
void		ft_cvntminus(t_vec3 *v);
void		ft_plus2vecs(t_vec3 *a, const t_vec3 *b);
void		ft_multivec(t_vec3 *v, const double b);
void		ft_dividevec(t_vec3 *v, const double b);
t_vec3		new_plus2v(const t_vec3 *u, const t_vec3 *v);
t_vec3		new_minus2v(const t_vec3 *u, const t_vec3 *v);
t_vec3		new_x2v(const t_vec3 *u, const t_vec3 *v);
t_vec3		new_xv(const double t, const t_vec3 *v);
t_vec3		new_dividev(t_vec3 *v, const double t);
double		ft_dot(const t_vec3 *u, const t_vec3 *v);
t_vec3		new_cross(const t_vec3 *u, const t_vec3 *v);
t_vec3		new_unitvector(t_vec3 *v);
void		v_init(t_vec3 *v, const double r, const double g, const double b);
void		ray_init(
				t_ray *ray, const t_point3 *origin, const t_vec3 *direction);
t_point3	get_at(t_ray *ray, const double t);
t_color		ray_color(t_ray *r);

#endif
