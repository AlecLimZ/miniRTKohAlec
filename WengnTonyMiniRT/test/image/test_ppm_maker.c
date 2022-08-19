/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ppm_maker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 22:31:43 by weng              #+#    #+#             */
/*   Updated: 2022/05/28 22:52:13 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

void	test_image8_2_ppm3(void)
{
	t_img8	*img;

	img = ft_image8_new(200, 100);
	ft_memset(img->data, 255, img->row * img->col * 3);
	if (ft_image8_2_ppm3(img, "test_p3.ppm") == 0)
		printf("ft_image8_2_ppm3: Error!\n");
	else
		printf("ft_image8_2_ppm3: OK\n");
	ft_image8_del(img);
}

void	test_image8_2_ppm6(void)
{
	t_img8	*img;

	img = ft_image8_new(100, 200);
	ft_memset(img->data, 255, img->row * img->col * 3);
	if (ft_image8_2_ppm6(img, "test_p6.ppm") == 0)
		printf("ft_image8_2_ppm6: Error!\n");
	else
		printf("ft_image8_2_ppm6: OK\n");
	ft_image8_del(img);
}

void	test_image_2_ppm(void)
{
	t_img	*img;
	t_vec	*colour;
	size_t	i;
	size_t	j;
	int		retval;

	img = ft_image_new(100, 200);
	colour = ft_vec3_new(0.5, 0.5, 0.5);
	i = -1;
	while (++i < img->row)
	{
		j = -1;
		while (++j < img->col)
			ft_image_set(img, i, j, colour);
	}
	retval = ft_image_2_ppm(img, "test_ppm.ppm", 6);
	if (retval == 0)
		printf("ft_image_2_ppm: Error!\n");
	else
		printf("ft_image_2_ppm: OK\n");
	ft_image_del(img);
	ft_vec_del(colour);
}

int	main(void)
{
	// test_image8_2_ppm3();  // not run since it's slow
	test_image8_2_ppm6();
	test_image_2_ppm();
	return (0);
}
