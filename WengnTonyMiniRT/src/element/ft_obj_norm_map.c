/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_norm_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:12:33 by weng              #+#    #+#             */
/*   Updated: 2022/06/10 13:42:01 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "element.h"

/* Generate a norm map based on a given pathname. The normal map is normalised
 * as unit vectors to remove any rounding effects during importing. */
t_img	*ft_norm_map(const char *pathname)
{
	t_img	*img;
	t_vec	vec;
	size_t	i;

	if (pathname == NULL)
		return (NULL);
	img = ft_ppm_2_image(pathname);
	i = img->row * img->col * 3;
	while (i-- > 0)
		img->data[i] = 2 * img->data[i] - 1;
	vec.size = 3;
	i = -1;
	while (++i < img->row * img->col)
	{
		vec.data = &img->data[i * 3];
		ft_vec_normalise(&vec);
	}
	return (img);
}

/* Update the 'norm' vector by using the 'colour' vector from a normal
 * map. The colour vector is freed, and the norm vector is updated. */
t_vec	*ft_bump_norm(t_vec *colour, t_vec *norm)
{
	t_vec	*bump;
	t_mat	*transform;

	bump = ft_vec4_new(colour->data[0], colour->data[1], colour->data[2], 0);
	transform = ft_affine_rotate(norm);
	bump = ft_mat_mul_vec(transform, bump);
	ft_vec_swap(norm, bump);
	ft_vec_del(colour);
	ft_vec_del(bump);
	ft_mat_del(transform);
	return (norm);
}
