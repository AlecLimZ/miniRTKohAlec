/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 12:59:41 by weng              #+#    #+#             */
/*   Updated: 2022/06/22 22:46:38 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "element.h"

/* Return a new plane object.
 * @param point		4D vector containing the coordinates of a point on the plane
 * @param norm		4D vector containing the normal of the plane
 * @param opt		pointer to a data structure containing the object options.
 * */
t_obj	*ft_plane_new(t_vec *point, t_vec *norm, t_opt *opt)
{
	t_obj	*plane;

	plane = ft_obj_new(point, norm, NULL, opt);
	if (plane == NULL)
		return (NULL);
	plane->intersect = ft_plane_intersect;
	plane->coefficient = NULL;
	plane->normal = ft_plane_normal;
	plane->checkerboard = ft_plane_checkerboard;
	return (plane);
}

/* Returns 1 if 'ray' intersects a 'plane', 0 otherwise. If intersection
 * occurs, the intersection point is stored in 'point', and normal
 * vector is stored in 'norm'; otherwise, 'point' and 'norm' are
 * unchanged.
 * @param object	pointer to a plane object.
 * @param ray		ray in world-coordinate.
 * @param point		pointer to store intersection point.
 * @param norm		pointer to store normal vector at intersection point.
 * */
int	ft_plane_intersect(t_obj *plane, t_ray *ray, t_vec *point, t_vec *norm)
{
	double	t;
	int		retval;

	ray = ft_ray_transform(plane->fr_world, ft_ray_copy(ray));
	retval = (eq_double(ray->dir->data[2], 0) == 0);
	if (retval == 1)
	{
		t = -ray->org->data[2] / ray->dir->data[2];
		point = ft_ray_calc_point(ray, t, point);
		norm = plane->normal(plane, ray, point, norm);
		ft_mat_mul_vec(plane->to_world, point);
		ft_mat_mul_vec(plane->to_world, norm);
		retval &= (eq_double(t, 0) == 0 && t > 0);
	}
	ft_ray_del(ray);
	return (retval);
}

/* Return the altered normal on a plane, given a point. */
t_vec	*ft_plane_norm_map(t_obj *plane, t_vec *point, t_vec *norm)
{
	double	x;
	double	y;
	t_vec	*colour;

	x = fmod(fmod(point->data[0], 10) + 10 + 5, 10) / 10;
	y = fmod(fmod(point->data[1], 10) + 10 + 5, 10) / 10;
	colour = ft_image_get(plane->norm_map,
			(int)(y * plane->norm_map->row),
			(int)(x * plane->norm_map->col));
	return (ft_bump_norm(colour, norm));
}

/* Calculate the normal vector of a plane. */
t_vec	*ft_plane_normal(t_obj *plane, t_ray *ray, t_vec *point, t_vec *norm)
{
	t_vec	*normal;

	if (eq_double(point->data[2], 0) == 0)
		ft_perror("Point is not on a given plane", EINVAL);
	normal = ft_vec4_new(0, 0, 1, 0);
	ft_vec_swap(norm, normal);
	ft_vec_del(normal);
	norm = ft_correct_normal(norm, ray);
	if (plane->norm_map != NULL)
		norm = ft_plane_norm_map(plane, point, norm);
	return (norm);
}
