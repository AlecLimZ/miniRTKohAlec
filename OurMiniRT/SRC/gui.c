/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 19:17:26 by Koh               #+#    #+#             */
/*   Updated: 2022/10/19 16:49:08 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

const char	*get_object_typename(const t_object *object)
{
	const char *const	name[] = {
	[AMBIENT] = "Ambient (ratio)",
	[CAMERA] = "Camera (FOV)",
	[LIGHT] = "Light (ratio)",
	[SPHERE] = "Sphere (radius)",
	[PLANE] = "Plane",
	[CYLINDER] = "Cylinder (radius, height)",
	[CONE] = "Cone (radius, height)",
	[LIGHT_BONUS] = "Light bonus (ratio)",
	};

	if (object != NULL
		&& object->type < (sizeof(name) / sizeof(*name))
		&& name[object->type])
		return (name[object->type]);
	return ("Unknown");
}

static void	display(t_object *c)
{
	printf("type: %s\n", get_object_typename(c));
	printf("x: %f\t y: %f\t z: %f\n", c->coor.x, c->coor.y, c->coor.z);
	printf("ox: %f\t oy: %f\t oz: %f\n",
		c->orientation.x, c->orientation.y, c->orientation.z);
}

static int	gui_render(t_app *app)
{
	static unsigned int		last_invalidated = 0;

	if (app->invalidated == 0)
		++app->invalidated;
	if (last_invalidated == app->invalidated)
		return (0);
	last_invalidated = app->invalidated;
	if (app->features & FEATURE_HELP)
	{
		help(app);
		return (0);
	}
	display(app->selected_object->content);
	benchmark(NULL);
	mlx_put_image_to_window(
		app->mlx_ptr, app->win_ptr, raytrace(app), 0, 0);
	benchmark("Raytracing");
	if (app->features & FEATURE_CAPTION)
		mlx_string_put(app->mlx_ptr, app->win_ptr, 16, 24, 0XFFFF00,
			(char *)get_object_typename(app->selected_object->content));
	return (0);
}

// https://harm-smits.github.io/42docs/libs/minilibx/events.html#x11-interface
// "  [TAB]NextObject  [ARROWS]movement  [I]Back  [O]Forward"
// "  [1]Light++  [2]Light--  [3]radius++"
// "  [4]radius--  [5]height++  [6]height--"
// "  [G]ammaCorrection  [W]indowSize  [R]eload  [E]xport";
void	create_window(t_app *app, int width, int height)
{
	char *const	title = "miniRT (Press H for Help)";

	if (app->win_ptr)
		mlx_destroy_window(app->mlx_ptr, app->win_ptr);
	if (app->image.ptr)
		mlx_destroy_image(app->mlx_ptr, app->image.ptr);
	app->image.ptr = mlx_new_image(app->mlx_ptr, width, height);
	app->image.addr = mlx_get_data_addr(
			app->image.ptr, &app->image.bits_per_pixel,
			&app->image.line_length, &app->image.endian);
	app->image.width = app->image.line_length / (app->image.bits_per_pixel / 8);
	app->image.height = height;
	printf("resolution %d %d\n", app->image.width, app->image.height);
	if (app->image.bits_per_pixel != 32 || app->image.endian != 0)
		app_exit(app, "Require 32bit color and little-endian (x86) platform");
	app->win_ptr = mlx_new_window(
			app->mlx_ptr, app->image.width, app->image.height, title);
	mlx_hook(app->win_ptr, 2, 1L << 0, gui_keydown, app);
	mlx_hook(app->win_ptr, 3, 1L << 1, gui_keyup, app);
	mlx_hook(app->win_ptr, 4, 1L << 2, gui_mouseup, app);
	mlx_hook(app->win_ptr, 17, 1L << 17, gui_exit, app);
}

// why macOs API missing mlx_get_screen_size??
// mlx_get_screen_size(app->mlx_ptr, &app->width, &app->height);
// beware: color int(argb) on x86 little-endian is char[b,g,r,a]
// mlxmetal may increase image-width somehow
void	start_gui(t_app *app, int width, int height)
{
	app->mlx_ptr = if_null_exit(mlx_init(), app);
	create_window(app, width, height);
	mlx_do_key_autorepeaton(app->mlx_ptr);
	mlx_loop_hook(app->mlx_ptr, gui_render, app);
	mlx_loop(app->mlx_ptr);
}

// float dir_x=0,dir_y=0,dir_z= +-1;
// rotate_x(&dir_y, &dir_z, app->camera->orientation.x);
// rotate_y(&dir_x, &dir_z, app->camera->orientation.y);
// rotate_z(&dir_x, &dir_y, app->camera->orientation.z);
// app->camera->coor.x += dir_x;
// app->camera->coor.y += dir_y;
// app->camera->coor.z += dir_z;
