/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light_ambient.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:03:17 by weng              #+#    #+#             */
/*   Updated: 2022/06/10 13:53:33 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "element.h"

/* Return a new ambient light.
 * @centre	4D vector representing the centre of the light
 * @ratio	inverse of constant attenuation constant kc, range [0, 1]
 * @colour	3D vector representing the colour of the light, each element
 * 			having the range [0, 1]
 */
t_light	*ft_ambient_new(double ratio, t_vec *colour)
{
	t_light	*light;

	colour = ft_vec_mul_scalar(colour, ratio);
	light = ft_light_new(NULL, NULL, NULL, colour);
	if (light == NULL)
		return (NULL);
	light->intense = ft_ambient_intensity;
	return (light);
}

/* Return the colour due to the ambient light source.
 * @light	light source
 * @ray		a ray originated from a point to a light source
 */
t_vec	*ft_ambient_intensity(t_light *light, t_ray *ray)
{
	(void) ray;
	return (ft_vec_copy(light->colour));
}
