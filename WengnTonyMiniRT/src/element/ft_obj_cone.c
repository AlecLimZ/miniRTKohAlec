/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_cone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 14:46:57 by weng              #+#    #+#             */
/*   Updated: 2022/06/22 17:05:16 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "element.h"

/* Return a new cone object.
 * @param ctr		4D vector containing the coordinates of the centre
 					of cone
 * @param orient	4D vector containning the orientation vector
 * @param height	height of the cone
 * @param opt		pointer to a data structure containing the object options
 * */
t_obj	*ft_cone_new(t_vec *ctr, t_vec *orient, double height, t_opt *opt)
{
	t_obj	*cone;
	t_vec	*dim;

	dim = ft_vec2_new(0, height);
	cone = ft_obj_new(ctr, orient, dim, opt);
	if (cone == NULL)
		return (NULL);
	cone->intersect = ft_obj_intersect;
	cone->coefficient = ft_cone_coefficient;
	cone->normal = ft_cone_normal;
	cone->checkerboard = ft_cone_checkerboard;
	return (cone);
}

/* Calculate the coefficient for cone and stores in 'coeff'. */
void	ft_cone_coefficient(t_obj *cone, t_ray *ray, double *coeff)
{
	(void) cone;
	coeff[0] = ft_vec_mul_dot(ray->dir, ray->dir)
		- 2 * pow(ray->dir->data[2], 2);
	coeff[1] = 2 * ft_vec_mul_dot(ray->org, ray->dir)
		- 4 * ray->org->data[2] * ray->dir->data[2];
	coeff[2] = ft_vec_mul_dot(ray->org, ray->org)
		- 2 * pow(ray->org->data[2], 2) - 1;
}

/* Return the altered normal on a cone, given a point. */
t_vec	*ft_cone_norm_map(t_obj *cone, t_vec *point, t_vec *norm)
{
	double	y;
	double	phi;
	t_vec	*colour;

	y = fmod(fmod(point->data[2], 10) + 10, 10) / 10;
	phi = atan2(point->data[1], point->data[0]);
	colour = ft_image_get(cone->norm_map,
			(int)(y * cone->norm_map->row),
			(int)((phi / M_PI / 2 + 0.5) * cone->norm_map->col));
	return (ft_bump_norm(colour, norm));
}

/* Calculate the normal vector at a point on a cone, and store it in
 * the 'normal' vector. If the point given is not on the surface, and
 * error message will be printed.
 * 
 * For this calculation, it the height of the cone is not checked, 
 * i.e. the cone is assumed to have infinite height.
 * 
 * Since it is assumed that the ray will not hit the object if it is
 * coming at the tangent, the ray will never hit the object at the
 * origin.
 * */
t_vec	*ft_cone_normal(t_obj *cone, t_ray *ray, t_vec *point, t_vec *norm)
{
	t_vec	*normal;

	(void) cone;
	if (eq_double(
			pow(point->data[0], 2) + pow(point->data[1], 2),
			pow(point->data[2], 2)) == 0)
		ft_perror("Point is not on a given cone", EINVAL);
	normal = ft_vec4_new(point->data[0], point->data[1], -point->data[2], 0.0);
	ft_vec_normalise(normal);
	ft_vec_swap(norm, normal);
	ft_vec_del(normal);
	norm = ft_correct_normal(norm, ray);
	if (cone->norm_map != NULL)
		norm = ft_cone_norm_map(cone, point, norm);
	return (norm);
}
