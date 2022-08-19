/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hloke <hloke@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 10:19:06 by hloke             #+#    #+#             */
/*   Updated: 2022/06/20 15:42:10 by hloke            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

t_image	*ft_mlx_image_new(void *mlx_ptr, int width, int height)
{
	t_image	*image;

	image = malloc(sizeof(t_image));
	if (image != NULL)
	{
		image->mlx_ptr = mlx_ptr;
		image->img_ptr = mlx_new_image(image->mlx_ptr, width, height);
		image->addr = mlx_get_data_addr(image->img_ptr, &image->bpp,
				&image->line_length, &image->endian);
		image->width = width;
		image->height = height;
	}
	return (image);
}

void	ft_mlx_image_del(t_image *image)
{
	mlx_destroy_image(image->mlx_ptr, image->img_ptr);
	free(image);
}

void	ft_mlx_image_put(t_mlx *mlx, t_image *image, int x, int y)
{
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, image->img_ptr, x, y);
	mlx->image = image;
}
