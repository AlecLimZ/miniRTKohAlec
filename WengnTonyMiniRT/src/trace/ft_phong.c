/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_phong.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 16:06:13 by weng              #+#    #+#             */
/*   Updated: 2022/06/10 13:53:30 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Return 1 if a ray hits a light, or 0 if its an object instead. */
int	ft_hit_light(t_light *light, t_ray *ray, t_list *objs)
{
	t_hit	*hit;
	t_vec	*vec;
	double	d_obj;
	double	d_light;

	vec = ft_vec_sub(ft_vec_copy(light->centre), ray->org);
	d_light = ft_vec_len(vec);
	ft_vec_del(vec);
	d_obj = INFINITY;
	hit = ft_hit_objs(ray, objs);
	if (hit != NULL)
		d_obj = hit->distance;
	ft_hit_del(hit);
	return (d_light < d_obj);
}

/* Return the intensity of one light, given a point and normal at
 * intersection, if a ray starting at the intersection point could hit
 * the light. Otherwise, return NULL. */
t_vec	*ft_light_intensity(t_hit *hit, t_light *light, t_list *objs)
{
	t_ray	*ray;
	double	factor;
	t_vec	*intensity;

	ray = ft_ray_new(ft_vec_copy(hit->point),
			ft_vec_sub(ft_vec_copy(light->centre), hit->point));
	factor = ft_vec_mul_dot(hit->norm, ray->dir);
	intensity = NULL;
	if (ft_hit_light(light, ray, objs) == 1 && factor > 0)
	{
		intensity = light->intense(light, ray);
		intensity = ft_vec_mul_scalar(intensity, factor);
	}
	ft_ray_del(ray);
	return (intensity);
}

/* Calculates the specular component of the Phong lighting model. The
 * surface's specular reflection colour is implicitly assumed to be
 * (1, 1, 1) simplistically under this implementation. */
double	ft_specular(t_hit *hit, t_light *light)
{
	t_vec	*lightdir;
	t_vec	*halfway;
	double	retval;

	if (hit->ray == NULL)
		return (0);
	lightdir = ft_vec_sub(ft_vec_copy(light->centre), hit->point);
	retval = 0;
	if (ft_vec_mul_dot(lightdir, hit->norm) > 0)
	{
		halfway = ft_vec_sub(ft_vec_copy(lightdir), hit->ray->dir);
		halfway = ft_vec_normalise(halfway);
		retval = ft_vec_mul_dot(hit->norm, halfway);
		ft_vec_del(halfway);
		if (retval < 0)
			retval = 0;
		else
			retval = pow(retval, 100);
	}
	ft_vec_del(lightdir);
	return (retval);
}

/* Return the total intensity at a point based on full Phong reflection
 * model, given multiple light and objects. */
t_vec	*ft_phong_reflection(
	t_hit *hit, t_light *ambient, t_list *lights, t_list *objs)
{
	t_vec	*vec;
	t_vec	*intensity;
	t_light	*light;
	double	specular;

	if (ambient != NULL)
		vec = ambient->intense(ambient, NULL);
	else
		vec = ft_vec3_new(0, 0, 0);
	while (lights != NULL)
	{
		light = lights->content;
		intensity = ft_light_intensity(hit, light, objs);
		if (intensity != NULL)
		{
			specular = ft_specular(hit, light);
			intensity = ft_vec_mul_scalar(intensity, 1 + specular);
			vec = ft_vec_add(vec, intensity);
			ft_vec_del(intensity);
		}
		lights = lights->next;
	}
	return (vec);
}

/* Limit all the components of a pixel to be less than 1, and return the
 * colour of the pixel. */
t_vec	*ft_limit_colour(
	t_hit *hit, t_light *ambient, t_list *lights, t_list *objs)
{
	t_vec	*colour;
	t_vec	*intensity;
	size_t	i;

	colour = hit->obj->colour(hit->obj, hit->point);
	intensity = ft_phong_reflection(hit, ambient, lights, objs);
	intensity = ft_vec_mul_elem(intensity, colour);
	i = -1;
	while (++i < intensity->size)
	{
		if (intensity->data[i] > 1)
			intensity->data[i] = 1;
	}
	ft_vec_del(colour);
	return (intensity);
}
