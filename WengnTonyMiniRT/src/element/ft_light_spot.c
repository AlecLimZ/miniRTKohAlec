/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light_spot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:49:29 by weng              #+#    #+#             */
/*   Updated: 2022/06/10 13:52:07 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "element.h"

/* Return a new spot light.
 * @centre	4D vector representing the centre of the light
 * @dir		4D vector representing the direction of the light
 * @ratio	1 - linear attenuation constant kl, range [0, 1]
 * @colour	3D vector representing the colour of the light, each element
 * 			having the range [0, 1]
 * 
 * The linear and quadratic attenuation function, kl and kq respectively,
 * are assumed to be 1. The spot light exponent p is assumed to be 10.
 */
t_light	*ft_spot_new(t_vec *ctr, t_vec *dir, double ratio, t_vec *colour)
{
	t_light	*light;
	t_vec	*param;

	param = ft_vec4_new(1, 1 - ratio, 0, 10);
	light = ft_light_new(ctr, ft_vec_normalise(dir), param, colour);
	if (light == NULL)
		return (NULL);
	light->intense = ft_spot_intensity;
	return (light);
}

/* Return the colour due to the spot light source.
 * Since spot light source has some direction associated to it, negative
 * dot product means that the light may be illuminating the point.
 * Conversely, 0 or positive dot product means the light cannot reach
 * the point.
 * @light	light source
 * @ray		a ray originated from a point to a light source
 */
t_vec	*ft_spot_intensity(t_light *light, t_ray *ray)
{
	double	numerator;

	numerator = -ft_vec_mul_dot(light->dir, ray->dir);
	if (numerator < 0)
		numerator = 0;
	numerator = pow(numerator, light->param->data[3]);
	return (ft_vec_mul_scalar(ft_point_intensity(light, ray), numerator));
}
