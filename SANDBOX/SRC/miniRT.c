/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:33:51 by leng-chu          #+#    #+#             */
/*   Updated: 2022/09/15 18:58:40 by leng-chu         ###   ########.fr       */
/*   Updated: 2021/12/07 11:48:40 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	deal_key(int key, void *param)
{
	int	*test;

	test = param;
	(void)key;
	ft_putchar('X');
	printf("param: %d\n", *test);
	return (0);
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1000, 500, "HELLO");
	img.img = mlx_new_image(mlx, 300, 300);
	img.addr = mlx_get_data_addr(img.img, &img.px, &img.len, &img.end);
	for (int i = 0; i < 300; i++)
		for (int j = 0; j < 150; j++)
			ft_pixel(&img, i, j, rgbtohex2(0.5, (double)j / 150.0, (double)i / 300.0, 0.25));
	mlx_put_image_to_window(mlx, mlx_win, img.img, 100, 0);
	
	int lol = 42;
	mlx_key_hook(mlx_win, deal_key, &lol);
	mlx_loop(mlx);
	(void)mlx_win;
	return (0);
}
