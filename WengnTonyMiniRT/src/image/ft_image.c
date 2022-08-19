/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_image.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:12:30 by weng              #+#    #+#             */
/*   Updated: 2022/06/07 14:58:47 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

/* Created a new empty image. */
t_img	*ft_image_new(size_t row, size_t col)
{
	t_img	*img;

	if (row == 0 || col == 0
		|| row * col / col != row || row * col * 3 / 3 != row * col)
		return (NULL);
	img = malloc(sizeof(t_img));
	if (img != NULL)
	{
		img->row = row;
		img->col = col;
		img->data = ft_calloc(row * col * 3, sizeof(double));
		if (img->data == NULL)
		{
			ft_image_del(img);
			return (NULL);
		}
	}
	return (img);
}

/* Delete an image */
void	ft_image_del(t_img *img)
{
	if (img == NULL)
		return ;
	free(img->data);
	free(img);
}

/* Update a pixel (i, j) of image 'img' with 'colour'. */
int	ft_image_set(t_img *img, size_t i, size_t j, t_vec *colour)
{
	if (i >= img->row || j >= img->col)
		return (0);
	ft_memmove(
		&img->data[(i * img->col + j) * 3], colour->data, 3 * sizeof(double));
	return (1);
}

/* Return the pixel (i, j) of image 'img' as a vector */
t_vec	*ft_image_get(t_img *img, size_t i, size_t j)
{
	t_vec	*vec;

	if (i >= img->row || j >= img->col)
		return (NULL);
	vec = ft_vec3_new(0, 0, 0);
	ft_memmove(
		vec->data, &img->data[(i * img->col + j) * 3], 3 * sizeof(double));
	return (vec);
}

/* Convert a double precision image to an 8 bit image. */
t_img8	*ft_image_2_image8(t_img *img)
{
	t_img8	*retval;
	size_t	i;

	retval = ft_image8_new(img->row, img->col);
	i = img->row * img->col * 3;
	while (i-- > 0)
		retval->data[i] = (int)(img->data[i] * 255.9999);
	return (retval);
}
