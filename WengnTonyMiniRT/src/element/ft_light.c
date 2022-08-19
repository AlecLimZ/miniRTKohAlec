/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 13:16:49 by weng              #+#    #+#             */
/*   Updated: 2022/06/10 12:18:48 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "element.h"

/* Return a new light source.
 * @centre	4D vector representing the centre of the light
 * @dir		4D vector representing the direction of the light
 * @param	4D vector representing the parameters of the light
 *			kc	constant attenuation constant
 * 			kl	linear attenuation constant
 * 			kq	quadratic attenuation constant
 * 			p	spot light exponent
 * @colour	3D vector representing the colour of the light, each element
 * 			having the range [0, 1]
 */
t_light	*ft_light_new(t_vec *ctr, t_vec *dir, t_vec *param, t_vec *colour)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	if (light == NULL)
		return (NULL);
	light->centre = ctr;
	if (dir == NULL)
		light->dir = NULL;
	else
		light->dir = ft_vec_normalise(dir);
	light->param = param;
	light->colour = colour;
	return (light);
}

void	ft_light_del(t_light *light)
{
	if (light == NULL)
		return ;
	ft_vec_del(light->centre);
	ft_vec_del(light->dir);
	ft_vec_del(light->param);
	ft_vec_del(light->colour);
	free(light);
}
