/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 19:17:26 by Koh               #+#    #+#             */
/*   Updated: 2022/09/18 11:37:55 by Koh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include "miniRT.h"



int	gui_input(unsigned int key, t_app *app)
{
	const char	map[127] = {
	[KEY_ONE] = '1', [KEY_TWO] = '2', [KEY_THREE] = '3', [KEY_FOUR] = '4',
	[KEY_FIVE] = '5', [KEY_SIX] = '6', [KEY_SEVEN] = '7', [KEY_EIGHT] = '8',
	[KEY_NINE] = '9', [KEY_ZERO] = '0',
	[KEY_A] = 'a', [KEY_B] = 'b', [KEY_C] = 'c', [KEY_D] = 'd', [KEY_E] = 'e',
	[KEY_F] = 'f', [KEY_G] = 'g', [KEY_H] = 'h', [KEY_I] = 'i', [KEY_J] = 'j',
	[KEY_K] = 'k', [KEY_L] = 'l', [KEY_M] = 'm', [KEY_N] = 'n', [KEY_O] = 'o',
	[KEY_P] = 'p', [KEY_Q] = 'q', [KEY_R] = 'r', [KEY_S] = 's', [KEY_T] = 't',
	[KEY_U] = 'u', [KEY_V] = 'v', [KEY_W] = 'w', [KEY_X] = 'x', [KEY_Y] = 'y',
	[KEY_Z] = 'z' };

printf("keycode %d\n", key);
	if (app->selected_object == NULL || key == KEY_TAB)
	{
		printf("here %p\n", app->selected_object);
		select_next(app);
	}

	if (key == KEY_A)
	{
		((t_object*)app->selected_object->content)->coor.z += 1;
		// float dir_x=0,dir_y=0,dir_z=1;
		// rotate_x(&dir_y, &dir_z, app->camera->orientation.x);
		// rotate_y(&dir_x, &dir_z, app->camera->orientation.y);
		// rotate_z(&dir_x, &dir_y, app->camera->orientation.z);
		// app->camera->coor.x += dir_x;
		// app->camera->coor.y += dir_y;
		// app->camera->coor.z += dir_z;
	}
	if (key == KEY_Z)
	{
		((t_object*)app->selected_object->content)->coor.z-=1;
		// float dir_x=0,dir_y=0,dir_z = -1;
		// rotate_x(&dir_y, &dir_z, app->camera->orientation.x);
		// rotate_y(&dir_x, &dir_z, app->camera->orientation.y);
		// rotate_z(&dir_x, &dir_y, app->camera->orientation.z);
		// app->camera->coor.x += dir_x;
		// app->camera->coor.y += dir_y;
		// app->camera->coor.z += dir_z;
	}
	if (key == KEY_ESC)
		app_exit(app, NULL);
	else if (key == KEY_DOWN)
		((t_object*)app->selected_object->content)->coor.y-=1;
	else if (key == KEY_UP)
		((t_object*)app->selected_object->content)->coor.y+=1;
	else if (key == KEY_RIGHT)
		((t_object*)app->selected_object->content)->coor.x+=1;
	else if (key == KEY_LEFT)
		((t_object*)app->selected_object->content)->coor.x-=1;
	else if (key == KEY_S)
		app->camera->orientation.x += PI * 2 / 8;
	else if (key == KEY_X)
		app->camera->orientation.x -= PI * 2 / 8;
	else if (key == KEY_D)
		app->camera->orientation.y += PI * 2 / 8;
	else if (key == KEY_C)
		app->camera->orientation.y -= PI * 2 / 8;
	else if (key == KEY_F)
		app->camera->orientation.z += PI * 2 / 8;
	else if (key == KEY_V)
		app->camera->orientation.z -= PI * 2 / 8;

	else if (key == KEY_N)
		app->render_mode = (app->render_mode + 1) % RENDER_MODE_END;
	else if (key < 127)
		ft_putchar_fd(map[key], 1);
	app->last_updated++;
	return (0);
}

static inline int	color(double r, double g, double b)
{
	return (((int)r << 16) + ((int)g << 8) + (int)b);
}

static void	*gradient(t_app *app)
{
	const double	r = 255.999 / (app->width - 1);
	const double	g = 255.999 / (app->height - 1);
	const double	b = 255.999 * .25;
	t_wh			size;

	size.h = -1;
	while (++size.h < app->height)
	{
		size.w = -1;
		while (++size.w < app->width)
			app->image.px[size.h * app->image.width + size.w]
				= color(size.w * r, (app->height - 1 - size.h) * g, b);
	}
	return (app->image.ptr);
}

// app->image.width instead of app->width, in case MLXMETAL wider image
static void	*ants(t_app *app)
{
	const int	fd = open("/dev/random", 0);
	int			i;

	i = app->image.width * app->height;
	read(fd, app->image.addr, i * 4);
	close(fd);
	while (i--)
		app->image.px[i] &= 0xFFFFFF;
	return (app->image.ptr);
}

void	*rt(t_app *app);
void	*rt2();

int	gui_render(t_app *app)
{
	static unsigned int		last_updated = 0;
	static unsigned long	tick = 0;
	const clock_t			begin = clock();
	const char	*const name[] = {
			[CAMERA] = "Camera",
			[LIGHT]	= "Light",
			[LIGHT_BONUS] = "Light bonus",
			[SPHERE] = "Sphere",
			[PLANE] = "Plane",
			[CYLINDER] = "Cylinder",
			[CONE] = "Cone",
		};

	++tick;
	if (1)
	{
		mlx_put_image_to_window(
			app->mlx_ptr, app->win_ptr, rt2(app), 0, 0);
		printf("raytracing %fs\n", (double)(clock() - begin) / CLOCKS_PER_SEC);
		
		mlx_string_put(app->mlx_ptr, app->win_ptr, 24, 24, 0XFFFF00,
			(char *)name[((t_object *)app->selected_object->content)->type]);
		
		mlx_string_put(app->mlx_ptr, app->win_ptr, 24, app->height - 30, 0xFFFF00,
			"TAB=Next_Object  UP=Move_Y+  DOWN=Move_Y-  LEFT=Move_X-  RIGHT=Move_X+  A=Move_Z+  Z=Move_Z-  N=Toggle_Render");
		
		return (0);
	}
	if (last_updated < app->last_updated)
	{
		tick = 0;
		printf("tick %lu\n", tick);
		last_updated = app->last_updated;
		mlx_clear_window(app->mlx_ptr, app->win_ptr);
		mlx_put_image_to_window(
			app->mlx_ptr, app->win_ptr, gradient(app), 0, 0);
		printf("gradient %fs\n", (double)(clock() - begin) / CLOCKS_PER_SEC);
	}
	else if (tick > 9999 && tick % 100 == 0)
	{
		mlx_put_image_to_window(
			app->mlx_ptr, app->win_ptr, ants(app), 0, 0);
		printf("ants in %fs\n", (double)(clock() - begin) / CLOCKS_PER_SEC);
	}
	return (0);
}
