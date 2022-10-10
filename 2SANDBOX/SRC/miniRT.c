/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:33:51 by leng-chu          #+#    #+#             */
/*   Updated: 2022/10/10 15:08:49 by leng-chu         ###   ########.fr       */
/*   Updated: 2021/12/07 11:48:40 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

# define WIN_W 1024
# define WIN_H 768
# define IMG_W 1024
# define IMG_H 768

typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
} t_mlx;

typedef struct s_sphere2
{
	t_vec3 center;
	double radius;
	t_color color;
} t_sphere2;

int	deal_key(int key, void *param)
{
	t_mlx	*mptr;

	mptr = param;
	printf("keycode: %d\n", key);
	if (key == 53)
	{
		mlx_destroy_window(mptr->mlx, mptr->mlx_win);
		exit(0);
	}
	return (0);
}

void	display(t_vec3 *v)
{
	printf("r: %.2f  |  g: %.2f  |  b: %.2f\n", v->rgb[0], v->rgb[1], v->rgb[2]);
}

void	write_color(t_color *pixel)
{
	printf("%d %d %d\n", (int)(pixel->rgb[0] * 255.999), (int)(pixel->rgb[1] * 255.999), (int)(pixel->rgb[2] * 255.999));
}

void sandbox(void)
{
	t_mlx	m;
	t_data	*iptr;
	t_vec3	origin;
//	t_vec3	dir;
	t_color	color;
//	t_sphere2 *sbox;

//	sbox = malloc(sizeof(t_sphere2) * 3);
	//initsphere2(sbox);
	v_init(&origin, 0, 0, 0);
	iptr = &m.img;
	m.mlx = mlx_init();
	m.mlx_win = mlx_new_window(m.mlx, WIN_W, WIN_H, "HELLO");
	iptr->img = mlx_new_image(m.mlx, IMG_W, IMG_H);
	iptr->addr = mlx_get_data_addr(iptr->img, &iptr->px, &iptr->len, &iptr->end);
	(void)color;
	for (int i = 0; i < IMG_W; i++)
	{
		for (int j = 0; j < IMG_H; j++)
		{
			ft_pixel(iptr, i, j, rgbtohex2(0, 0.25, 0.25, 0.25));
		}
	}
	mlx_put_image_to_window(m.mlx, m.mlx_win, iptr->img, 0, 0);
	mlx_key_hook(m.mlx_win, deal_key, &m);
	mlx_loop(m.mlx);
}

int	ray_intersect(t_vec3 *orig, t_vec3 *dir, double *t0, t_sphere2 *sp)
{
	t_vec3 L;

	L = new_minus2v(&sp->center, orig);
	display(&L);
	double tca = ft_dot(&L, dir);
	double d2 = ft_dot(&L, &L) - tca * tca;
	if (d2 > sp->radius * sp->radius)
		return 0;
	double thc = sqrt(sp->radius * sp->radius - d2);
	*t0 = tca - thc;
	double t1 = tca + thc;
	if (*t0 < 0)
		*t0 = t1;
	if (*t0 < 0)
		return 0;
	return 1;
}
	
t_color cast_ray(t_vec3 *orig, t_vec3 *dir, t_sphere2 *sp)
{
	t_color bg;
	
	v_init(&bg, 0.2, 0.7, 0.8);
	double sphere_dist = INFINITY; // to be used as t0 later
	if (!ray_intersect(orig, dir, &sphere_dist, sp))
		return (bg);
	printf("get sp color\n");
	return (sp->color);
}

void	render(void)
{
	t_mlx	m;
	t_data	*iptr;

	// new ori, dir, color & sphere, fov(depth)
	t_vec3 ori; // init with 0,0,0
	t_color	c; // inside loop
	t_vec3 dir; // inside loop // normalized by using unit_vector fct
	t_sphere2 sp; // set -3, 0, 16 for center | radius 2 | color 0.4, 0.4, 0.3
	int	fov; // fov = M_PI / 2

	fov = M_PI / 2.;
	v_init(&ori, 0, 0, 0);
	v_init(&sp.center, -3, 0, -16);
	v_init(&sp.color, 0.4, 0.4, 0.3);
	sp.radius = 2;

	iptr = &m.img;
	m.mlx = mlx_init();
	m.mlx_win = mlx_new_window(m.mlx, WIN_W, WIN_H, "HELLO");
	iptr->img = mlx_new_image(m.mlx, IMG_W, IMG_H);
	iptr->addr = mlx_get_data_addr(iptr->img, &iptr->px, &iptr->len, &iptr->end);
	for (int i = 0; i < IMG_H; i++)
	{
		for (int j = 0; j < IMG_W; j++)
		{
			double x = (2 * (j + 0.5) / (double)IMG_W - 1) * tan(fov/2.) * IMG_W / (double)IMG_H;
			double y = (2 * (i + 0.5) / (double)IMG_H - 1) * tan(fov/2.);
			v_init(&dir, x, y, -1);
			dir = new_unitvector(&dir);
			c = cast_ray(&ori, &dir, &sp);
			ft_pixel(iptr, j, i, rgbtohex2(0, c.rgb[0], c.rgb[1], c.rgb[2]));
		}
	}
	mlx_put_image_to_window(m.mlx, m.mlx_win, iptr->img, 0, 0);
	mlx_key_hook(m.mlx_win, deal_key, &m);
	mlx_loop(m.mlx);
}

int main(void)
{
	render();
	return (0);
}
