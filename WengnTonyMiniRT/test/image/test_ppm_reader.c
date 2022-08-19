/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ppm_reader.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 16:20:25 by weng              #+#    #+#             */
/*   Updated: 2022/06/07 17:35:30 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

void	test_reader(void)
{
	t_img	*img;
	t_vec	*colour;
	t_vec	*target;

	img = ft_ppm_2_image("../map/golfball.ppm");
	colour = ft_image_get(img, 389, 774);
	target = ft_vec3_new(160 / 255.0, 106 / 255.0, 255 / 255.0);
	if (eq_vec(colour, target) == 0)
		printf("ft_ppm_2_image: Error!\n");
	else
		printf("ft_ppm_2_image: OK\n");
	ft_image_del(img);
	ft_vec_del(colour);
	ft_vec_del(target);
}

int	main(void)
{
	test_reader();
	return (0);
}
