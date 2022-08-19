/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:29:53 by weng              #+#    #+#             */
/*   Updated: 2022/06/02 23:24:38 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* Trace a ray to determine and return the colour of a particular pixel.
 * If a ray hits an object, it will return the colour of diffused
 * lighting. Otherwise, it will return the ambient lighting. */
t_vec	*ft_trace(t_ray *ray, t_light *ambient, t_list *lights, t_list *objs)
{
	t_hit	*hit;
	t_vec	*vec;

	hit = ft_hit_objs(ray, objs);
	if (hit == NULL)
	{
		if (ambient != NULL)
			return (ambient->intense(ambient, NULL));
		else
			return (ft_vec3_new(0, 0, 0));
	}
	vec = ft_limit_colour(hit, ambient, lights, objs);
	ft_hit_del(hit);
	return (vec);
}

/* Render a scene by looping through all the */
t_img	*ft_render(t_cam *cam, t_light *ambient, t_list *lights, t_list *objs)
{
	t_img	*img;
	t_ray	*ray;
	t_vec	*colour;
	int		i;
	int		j;

	img = ft_image_new(cam->reso_y, cam->reso_x);
	i = -1;
	while (++i < cam->reso_y)
	{
		j = -1;
		while (++j < cam->reso_x)
		{
			ray = ft_camera_ray(cam, j, i);
			colour = ft_trace(ray, ambient, lights, objs);
			ft_image_set(img, i, j, colour);
			ft_ray_del(ray);
			ft_vec_del(colour);
		}
	}
	return (img);
}
