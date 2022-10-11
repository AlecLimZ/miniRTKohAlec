/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:33:51 by leng-chu          #+#    #+#             */
/*   Updated: 2022/10/11 15:14:47 by leng-chu         ###   ########.fr       */
/*   Updated: 2021/12/07 11:48:40 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

#define SPSIZE	4
#define LGSIZE	1

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
	printf("%d %d %d\n",
		(int)(pixel->rgb[0] * 255.999),
		(int)(pixel->rgb[1] * 255.999),
		(int)(pixel->rgb[2] * 255.999));
}

//len is between origin & object center
//sp is pointing one of spheres
int	ray_intersect(t_vec3 *orig, t_vec3 *dir, double *t0, t_sphere *sp)
{
	t_vec3	len;
	double	tca;
	double	d2;
	double	thc;
	double	t1;

	len = new_minus2v(&sp->center, orig);
	tca = ft_dot(&len, dir);
	d2 = ft_dot(&len, &len) - tca * tca;
	if (d2 > sp->radius * sp->radius)
		return (0);
	thc = sqrt(sp->radius * sp->radius - d2);
	*t0 = tca - thc;
	t1 = tca + thc;
	if (*t0 < 0)
		*t0 = t1;
	if (*t0 < 0)
		return (0);
	return (1);
}

// point & N for vectors?
// point = hit
// you need to look for a way to count the total of spheres to be
// used for the loop
//int	scene_intersect(t_ray *ray, t_color *clr, t_sphere *splist)
int	scene_intersect(t_setting *set, t_material *clr)
{
	double	spheres_dist;
	double	dist_i;

	spheres_dist = INFINITY;
	for (size_t i = 0; i < SPSIZE; i++)
	{
		if (ray_intersect(&set->ray.ori, &set->ray.dir, &dist_i,
				&set->splist[i]) && dist_i < spheres_dist)
		{
			spheres_dist = dist_i;
			set->ray.pthit = new_xv(dist_i, &set->ray.dir);
			set->ray.pthit = new_plus2v(&set->ray.ori, &set->ray.pthit);
			set->ray.norm = new_minus2v(&set->ray.pthit, &set->splist[i].center);
			set->ray.norm = new_unitvector(&set->ray.norm);
			*clr = set->splist[i].material;
		}
	}
	return (spheres_dist < 1000);
}

// spere_dist to be used as t0 inside the ray_intersect fct
//t_color	cast_ray(t_ray *ray, t_sphere *splist)
// no vector for point(hit) & N (norm) yet
t_color	cast_ray(t_setting *set)
{
	t_color		bg;
	t_material	clr;
	t_vec3		light_dir;
	double		dot;
	double		diffuse_light_intensity;

	v_init(&bg, 0.2, 0.7, 0.8);
	//if (!scene_intersect(&set->ray, &clr, set->splist))
	if (!scene_intersect(set, &clr))
		return (bg);
	diffuse_light_intensity = 0;
	for (size_t i = 0; i < LGSIZE; i++)
	{
		light_dir = new_minus2v(&set->lights[i].position, &set->ray.pthit);
		light_dir = new_unitvector(&light_dir);
		dot = ft_dot(&light_dir, &set->ray.norm);
		if (0.0 < dot)
			diffuse_light_intensity += set->lights[i].intensity * dot;
		else
			diffuse_light_intensity += set->lights[i].intensity * 0.0;
	}
	return (new_xv(diffuse_light_intensity, &clr.diffuse_color));
}

void	mlx_action(t_mlx *m)
{
	mlx_put_image_to_window(m->mlx, m->mlx_win, m->img.img, 0, 0);
	mlx_key_hook(m->mlx_win, deal_key, m);
	mlx_loop(m->mlx);
}

void	loop_action(t_setting *set, int i, int j)
{
	double	x;
	double	y;

	x = (2 * (j + 0.5) / (double)IMG_W - 1)
		* tan(set->fov / 2.) * IMG_W / (double)IMG_H;
	y = (2 * (i + 0.5) / (double)IMG_H - 1) * tan(set->fov / 2.);
	v_init(&set->ray.dir, x, y, -1);
	set->ray.dir = new_unitvector(&set->ray.dir);
	set->colorout = cast_ray(set);
}

void	render(t_mlx *m, t_setting *set)
{
	int	i;
	int	j;

	i = -1;
	while (++i < IMG_H)
	{
		j = -1;
		while (++j < IMG_W)
		{
			loop_action(set, i, j);
			ft_pixel(&m->img, j, i, rgbtohex2(0, set->colorout.rgb[0],
					set->colorout.rgb[1], set->colorout.rgb[2]));
		}
	}
	mlx_action(m);
}

void	ft_initlg(t_light *lights)
{
	v_init(&lights[0].position, -20, 20, 20);
	lights[0].intensity = 1.5;
}

// setup for spheres
// currently material contains diffuse vector
void	ft_initsp(t_sphere *splist)
{
	t_material	ivory;
	t_material	red_rubber;

	v_init(&ivory.diffuse_color, 0.4, 0.4, 0.3);
	v_init(&red_rubber.diffuse_color, 0.3, 0.1, 0.1);
	v_init(&splist[3].center, 7, 5, -18);
	splist[3].material = ivory;
	splist[3].radius = 4;
	v_init(&splist[2].center, 1.5, -0.5, -18);
	splist[2].material = red_rubber;
	splist[2].radius = 3;
	v_init(&splist[1].center, -1.0, -1.5, -12);
	splist[1].material = red_rubber;
	splist[1].radius = 2;
	v_init(&splist[0].center, -3, 0, -16);
	splist[0].material = ivory;
	splist[0].radius = 2;
}

// setting for new ori, dir, colorout, fov
// fov 1 == (int)MP_PI / 2
// setup the sphere objects
void	ft_init(t_mlx *m, t_setting *set)
{
	t_data	*iptr;

	iptr = &m->img;
	m->mlx = mlx_init();
	m->mlx_win = mlx_new_window(m->mlx, WIN_W, WIN_H, "HELLO");
	iptr->img = mlx_new_image(m->mlx, IMG_W, IMG_H);
	iptr->addr = mlx_get_data_addr(iptr->img,
			&iptr->px, &iptr->len, &iptr->end);
	set->fov = 1;
	v_init(&set->ray.ori, 0, 0, 0);
	v_init(&set->ray.dir, 0, 0, 0);
	v_init(&set->ray.norm, 0, 0, 0);
	v_init(&set->ray.pthit, 0, 0, 0);
	v_init(&set->colorout, 0, 0, 0);
	set->splist = malloc(sizeof(t_sphere) * SPSIZE);
	set->lights = malloc(sizeof(t_sphere) * LGSIZE);
	ft_initsp(set->splist);
	ft_initlg(set->lights);
}

int	main(void)
{
	t_mlx		m;
	t_setting	set;

	ft_init(&m, &set);
	render(&m, &set);
	return (0);
}
