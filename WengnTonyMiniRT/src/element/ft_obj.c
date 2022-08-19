/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 11:40:38 by weng              #+#    #+#             */
/*   Updated: 2022/06/20 21:16:41 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "element.h"

/* Return a new 2nd order object.
 * @param ctr		4D vector containing the coordinates of the centre of object
 * @param orient	4D vector containing the orientation vector
 * @param dim		2D vector containing the radius and height of object
 * @param opt		pointer to a data structure containing the object options
 * */
t_obj	*ft_obj_new(t_vec *ctr, t_vec *orient, t_vec *dim, t_opt *opt)
{
	t_obj	*obj;

	obj = malloc(sizeof(t_obj));
	if (obj == NULL)
		return (NULL);
	obj->dimension = dim;
	obj->base_colour = opt->colour;
	obj->centre = ctr;
	orient = ft_vec_normalise(orient);
	obj->rotate = ft_affine_rotate(orient);
	ft_vec_del(orient);
	obj->to_world = ft_affine_transform(obj->centre, obj->rotate);
	obj->fr_world = ft_mat_affine_inverse(ft_mat_copy(obj->to_world));
	if (obj->to_world == NULL || obj->fr_world == NULL)
	{
		ft_obj_del(obj);
		return (NULL);
	}
	obj->colour = ft_obj_colour;
	obj->checkerboard = NULL;
	obj->disruption = opt->disruption;
	obj->norm_map = ft_norm_map(opt->norm_map);
	free(opt->norm_map);
	return (obj);
}

/* Delete an object. */
void	ft_obj_del(t_obj *obj)
{
	if (obj == NULL)
		return ;
	ft_vec_del(obj->dimension);
	ft_vec_del(obj->base_colour);
	ft_vec_del(obj->centre);
	ft_mat_del(obj->rotate);
	ft_mat_del(obj->to_world);
	ft_mat_del(obj->fr_world);
	ft_image_del(obj->norm_map);
	free(obj);
}

/* Returns 1 if 'ray' intersects an object 'obj', 0 otherwise. If
 * intersection occurs, the intersection point is stored in 'point', and
 * normal vector is stored in 'norm'; otherwise, 'point' and 'norm' are
 * unchanged.
 * @param obj	pointer to an object.
 * @param ray	ray in world-coordinate.
 * @param point	pointer to store intersection point.
 * @param norm	pointer to store normal vector at intersection point.
 * */
int	ft_obj_intersect(t_obj *obj, t_ray *ray, t_vec *point, t_vec *norm)
{
	double	co[3];
	double	t;
	double	discri;
	int		retval;

	ray = ft_ray_transform(obj->fr_world, ft_ray_copy(ray));
	obj->coefficient(obj, ray, co);
	discri = pow(co[1], 2) - 4 * co[0] * co[2];
	retval = ((eq_double(discri, 0) == 0) && discri > 0);
	if (retval == 1)
	{
		t = -(co[1] + sqrt(discri) * (1 - 2 * (co[0] < 0))) / (2 * co[0]);
		point = ft_ray_calc_point(ray, t, point);
		if (eq_double(t, 0) == 1 || t <= 0
			|| fabs(point->data[2]) > obj->dimension->data[1] / 2)
			t = -(co[1] - sqrt(discri) * (1 - 2 * (co[0] < 0))) / (2 * co[0]);
		point = ft_ray_calc_point(ray, t, point);
		norm = obj->normal(obj, ray, point, norm);
		retval = (fabs(point->data[2]) <= obj->dimension->data[1] / 2);
		ft_mat_mul_vec(obj->to_world, point);
		ft_mat_mul_vec(obj->to_world, norm);
		retval &= (eq_double(t, 0) == 0 && t > 0);
	}
	ft_ray_del(ray);
	return (retval);
}

/* Correct the direction of the normal vector from the surface based on
 * the direction of the ray. Returns the corrected normal.
 *
 * The dot product of the ray direction vector and normal should be less
 * than or equal to 0. Else, the normal should be reversed.
 */
t_vec	*ft_correct_normal(t_vec *norm, t_ray *ray)
{
	double	dot;

	dot = ft_vec_mul_dot(norm, ray->dir);
	if (dot > 0)
		norm = ft_vec_mul_scalar(norm, -1);
	return (norm);
}

/* Implement the colour disruption when appropriate. */
t_vec	*ft_obj_colour(t_obj *obj, t_vec *point)
{
	t_vec	*colour;

	if (obj->disruption == 0 || obj->checkerboard == NULL)
		return (ft_vec_copy(obj->base_colour));
	point = ft_mat_mul_vec(obj->fr_world, ft_vec_copy(point));
	colour = obj->checkerboard(obj, point);
	ft_vec_del(point);
	return (colour);
}
