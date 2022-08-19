/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light_point.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:18:50 by weng              #+#    #+#             */
/*   Updated: 2022/06/10 13:52:30 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "element.h"

/* Return a new point light.
 * @centre	4D vector representing the centre of the light
 * @ratio	1 - linear attenuation constant kl, range [0, 1]
 * @colour	3D vector representing the colour of the light, each element
 * 			having the range [0, 1]
 * 
 * The linear and quadratic attenuation function, kl and kq respectively,
 * are assumed to be 1.
 */
t_light	*ft_point_new(t_vec *ctr, double ratio, t_vec *colour)
{
	t_light	*light;
	t_vec	*param;

	param = ft_vec3_new(1, 1 - ratio, 0);
	light = ft_light_new(ctr, NULL, param, colour);
	if (light == NULL)
		return (NULL);
	light->intense = ft_point_intensity;
	return (light);
}

/* Return the colour due to the point light source.
 * @light	light source
 * @ray		a ray originated from a point to a light source
 */
t_vec	*ft_point_intensity(t_light *light, t_ray *ray)
{
	t_vec	*vec;
	double	distance;
	double	fraction;

	vec = ft_vec_sub(ft_vec_copy(light->centre), ray->org);
	distance = ft_vec_len(vec);
	fraction = 1 / (
			light->param->data[0]
			+ light->param->data[1] * distance
			+ light->param->data[2] * distance * distance);
	ft_vec_del(vec);
	return (ft_vec_mul_scalar(ft_vec_copy(light->colour), fraction));
}
