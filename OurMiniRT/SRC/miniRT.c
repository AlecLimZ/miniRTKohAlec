/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:33:51 by leng-chu          #+#    #+#             */
/*   Updated: 2022/10/13 13:55:13 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// app.last_updated = 1 to trigger first render
static void	init_app(t_app *app)
{
	*app = (t_app){.mini = 1 };
}

static void	load_scene_or_exit(t_app *app, char *filepath)
{
	app->scene_file = filepath;
	parse_file(filepath, app);
	select_next(app);
}

// why macOs API missing mlx_get_screen_size??
// mlx_get_screen_size(app->mlx_ptr, &app->width, &app->height);
// beware: color int(argb) on x86 little-endian is char[b,g,r,a]
// mlxmetal may increase image-width somehow
void	start_gui(t_app *app, int width, int height)
{
	const int	is_first = (app->mlx_ptr == NULL);

	if (is_first)
		app->mlx_ptr = if_null_exit(mlx_init(), app);
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
	app->win_ptr = mlx_new_window(app->mlx_ptr, app->image.width, app->image.height, 
		"miniRT "
		"TAB=Next_Object  UP=Move_Y+  DOWN=Move_Y-  LEFT=Move_X-  "
		"RIGHT=Move_X+  A=Move_Z+  Z=Move_Z-  "
		"G=Gamma_Correction  T=Toggle_Size  R=Reload_Scene  P=Print"
	);
	mlx_hook(app->win_ptr, KEY_PRESS_EVENT, KEY_PRESS_MASK, gui_input, app);
	mlx_hook(app->win_ptr, DESTROY_NOTIFY_EVENT, STRUCTURE_NOTIFY_MASK, gui_exit, app);
	if (is_first)
	{
		mlx_do_key_autorepeaton(app->mlx_ptr);
		mlx_loop_hook(app->mlx_ptr, gui_render, app);
		mlx_loop(app->mlx_ptr);
	}
}

int	main(int argc, char **argv)
{
	t_app		app;

	if (argc != 2)
		app_exit(&app, "Require 1 rt file");
	init_app(&app);
	load_scene_or_exit(&app, argv[1]);
	start_gui(&app, 1600, 900);
	app_exit(&app, "Unexpected GUI failure");
}
