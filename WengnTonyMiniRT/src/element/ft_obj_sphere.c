/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 22:53:28 by weng              #+#    #+#             */
/*   Updated: 2022/06/22 17:05:16 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "element.h"

/* Return a new sphere object.
 * @param ctr		4D vector containing the coordinates of the centre of sphere
 * @param orient	4D vector containning the orientation vector
 * @param dim		2D vector containing the radius and height of sphere.
 * 					Setting height more than double the radius will not
 * 					have any effect.
 * @param opt		pointer to a data structure containing the object options
 * */
t_obj	*ft_sphere_new(t_vec *ctr, t_vec *orient, t_vec *dim, t_opt *opt)
{
	t_obj	*sp;

	sp = ft_obj_new(ctr, orient, dim, opt);
	if (sp == NULL)
		return (NULL);
	sp->intersect = ft_obj_intersect;
	sp->coefficient = ft_sphere_coefficient;
	sp->normal = ft_sphere_normal;
	sp->checkerboard = ft_sphere_checkerboard;
	return (sp);
}

/* Calculate the coefficient for sphere and stores in 'coeff'. */
void	ft_sphere_coefficient(t_obj *sp, t_ray *ray, double *coeff)
{
	coeff[0] = ft_vec_mul_dot(ray->dir, ray->dir);
	coeff[1] = 2 * ft_vec_mul_dot(ray->org, ray->dir);
	coeff[2] = ft_vec_mul_dot(ray->org, ray->org)
		- pow(sp->dimension->data[0], 2) - 1;
}

/* Return the altered normal on a sphere, given a point. */
t_vec	*ft_sphere_norm_map(t_obj *sp, t_vec *point, t_vec *norm)
{
	double	theta;
	double	phi;
	t_vec	*colour;

	theta = acos(point->data[2] / sp->dimension->data[0]);
	phi = atan2(point->data[1], point->data[0]);
	colour = ft_image_get(sp->norm_map,
			(int)(theta / M_PI * sp->norm_map->row),
			(int)((phi / M_PI / 2 + 0.5) * sp->norm_map->col));
	return (ft_bump_norm(colour, norm));
}

/* Calculate the normal vector at a point on a sphere, and store it in
 * the 'normal' vector. If the point given is not on the surface, and
 * error message will be printed. */
t_vec	*ft_sphere_normal(t_obj *sp, t_ray *ray, t_vec *point, t_vec *norm)
{
	t_vec	*normal;

	if (eq_double(
			ft_vec_mul_dot(point, point),
			pow(sp->dimension->data[0], 2) + 1) == 0)
		ft_perror("Point is not on a given sphere", EINVAL);
	normal = ft_vec4_new(0, 0, 0, 1);
	normal = ft_vec_sub(normal, point);
	normal = ft_vec_mul_scalar(normal, -1);
	ft_vec_normalise(normal);
	ft_vec_swap(norm, normal);
	ft_vec_del(normal);
	norm = ft_correct_normal(norm, ray);
	if (sp->norm_map != NULL)
		norm = ft_sphere_norm_map(sp, point, norm);
	return (norm);
}
