/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:33:51 by leng-chu          #+#    #+#             */
/*   Updated: 2022/09/16 17:01:04 by leng-chu         ###   ########.fr       */
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

void	display(t_vec3 *v)
{
	printf("r: %.2f  |  g: %.2f  |  b: %.2f\n", v->rgb[0], v->rgb[1], v->rgb[2]);
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	// Image
	const double	aspect_ratio = 16.0 / 9.0;
	const int		img_w = 400;
	const int		img_h = (int)(img_w / aspect_ratio);

	// Camera
	double	viewport_height = 2.0;
	double	viewport_width = aspect_ratio * viewport_height;
	double	focal_length = 1.0;

	t_point3	origin;
	v_init(&origin, 0, 0, 0);

	t_vec3	horizontal;
	v_init(&horizontal, viewport_width, 0, 0);

	t_vec3	vertical;
	v_init(&vertical, 0, viewport_height, 0);

	t_vec3	lower_left_corner;
	t_vec3	h;
	t_vec3	v;
	t_vec3	fl;

	h =  new_dividev(&horizontal, 2);
	v =  new_dividev(&vertical, 2);
	v_init(&fl, 0, 0, focal_length);
	lower_left_corner = new_minus2v(&origin, &h);
	lower_left_corner = new_minus2v(&lower_left_corner, &v);
	lower_left_corner = new_minus2v(&lower_left_corner, &fl);

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1000, 500, "HELLO");
	img.img = mlx_new_image(mlx, img_w, img_h);
	img.addr = mlx_get_data_addr(img.img, &img.px, &img.len, &img.end);

//t_color ray_color(t_ray *r)	
	t_ray	r;
	t_color	fa;
	t_vec3	dirr;
	t_vec3	ur;
	t_vec3	vr;
	double	du;
	double	dv;

	for (int j = img_h - 1; j >= 0; --j)
	{
		for (int i = 0; i < img_w; ++i)
		{
			du = (double)i / (img_w - 1);
			dv = (double)j / (img_h - 1);
			ur = new_xv(du, &horizontal);
			vr = new_xv(dv, &vertical);
			dirr = new_plus2v(&lower_left_corner, &ur);
			dirr = new_plus2v(&dirr, &vr);
			dirr = new_minus2v(&dirr, &origin);

			ray_init(&r, &origin, &dirr);
			fa = ray_color(&r);
			ft_pixel(&img, i, j, rgbtohex2(0.0, fa.rgb[0], fa.rgb[1], fa.rgb[2]));
		}
	}


	mlx_put_image_to_window(mlx, mlx_win, img.img, 100, 0);
	int lol = 42;
	mlx_key_hook(mlx_win, deal_key, &lol);
	mlx_loop(mlx);
	(void)mlx_win;
	return (0);
}
	
//	(void)img_h;
//	mlx = mlx_init();
//	mlx_win = mlx_new_window(mlx, 1000, 500, "HELLO");
//	img.img = mlx_new_image(mlx, 300, 300);
//	img.addr = mlx_get_data_addr(img.img, &img.px, &img.len, &img.end);
//	for (int i = 0; i < 300; i++)
//		for (int j = 0; j < 150; j++)
//			ft_pixel(&img, i, j, rgbtohex2(0.5, (double)j / 150.0, (double)i / 300.0, 0.25));
//	mlx_put_image_to_window(mlx, mlx_win, img.img, 100, 0);
//	
//	int lol = 42;
//	mlx_key_hook(mlx_win, deal_key, &lol);
//	mlx_loop(mlx);
//	(void)mlx_win;
