/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 11:25:04 by hloke             #+#    #+#             */
/*   Updated: 2022/06/23 23:32:11 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

/*
 * Colour vector contains rgb value in range (0, 1).
 * Bit shifting is required to create integer value from color hex code
 */
static int	ft_convert_rgb(t_vec *color)
{
	int	rgb[3];

	rgb[0] = color->data[0] * 255.9999;
	rgb[1] = color->data[1] * 255.9999;
	rgb[2] = color->data[2] * 255.9999;
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

/* Draw a pixel to an image. */
static void	ft_pixel_draw(t_image *image, int x, int y, int color)
{
	char	*dst;

	if (image == NULL
		|| x < 0 || y < 0 || x > image->width || y > image->height)
		return ;
	dst = image->addr + (y * image->line_length + x * (image->bpp / 8));
	*((unsigned int *) dst) = color;
}

/* Draw a t_img8 image onto a t_image image. */
void	ft_draw_image(t_image *image, t_img *img)
{
	size_t	i;
	size_t	j;
	int		color;
	t_vec	*vec;

	if (img == NULL)
		ft_perror("ft_draw_image: Image8 file is not found", EINVAL);
	i = -1;
	while (++i < img->row)
	{
		j = -1;
		while (++j < img->col)
		{
			vec = ft_image_get(img, i, j);
			if (vec == NULL)
				ft_perror("ft_draw_img8: Invalid color data", EINVAL);
			color = ft_convert_rgb(vec);
			ft_pixel_draw(image, j, i, color);
			ft_vec_del(vec);
		}
	}
}
