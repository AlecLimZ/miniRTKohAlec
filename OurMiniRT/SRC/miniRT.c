/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:33:51 by leng-chu          #+#    #+#             */
/*   Updated: 2022/09/17 23:23:06 by Koh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// app.last_updated = 1 to trigger first render
static void	init_app(t_app *app)
{
	*app = (t_app){.last_updated = 1, .width = 800, .height = 600};
}

static void	load_scene_or_exit(t_app *app, char *filepath)
{
	parse_file(filepath, app);
	printf("lstsize %d\n", ft_lstsize(app->objects));
}

// why macOs API missing mlx_get_screen_size??
// mlx_get_screen_size(app->mlx_ptr, &app->width, &app->height);
// todo: support little-endian (x86), eg remove ants()
static void	start_gui(t_app *app)
{
	app->mlx_ptr = if_null_exit(mlx_init(), app);
	app->win_ptr = mlx_new_window(app->mlx_ptr, app->width, app->height, "RT");
	app->image.ptr = mlx_new_image(app->mlx_ptr, app->width, app->height);
	app->image.addr = mlx_get_data_addr(
			app->image.ptr, &app->image.bits_per_pixel,
			&app->image.line_length, &app->image.endian);
	if (app->image.line_length > app->image.bits_per_pixel * app->width)
		printf("mlx image wider than requested by %d px\n",
			(app->image.line_length / app->image.bits_per_pixel / 8)
			- app->width);
	if (app->image.bits_per_pixel != 32)
		app_exit(app, "Require 32bit pixel");
	if (app->image.endian != 0)
		app_exit(app, "Require little endian, eg x86");
	mlx_do_key_autorepeaton(app->mlx_ptr);
	mlx_hook(app->win_ptr, 17, 1L << 17, gui_exit, app);
	mlx_hook(app->win_ptr, 2, 1L << 0, gui_input, app);
	mlx_loop_hook(app->mlx_ptr, gui_render, app);
	mlx_loop(app->mlx_ptr);
}

int	main(int argc, char **argv)
{
	t_app		app;

	init_app(&app);
	if (argc != 2)
		app_exit(&app, "Require 1 rt file");
	load_scene_or_exit(&app, argv[1]);
	start_gui(&app);
	app_exit(&app, "Unexpected GUI failure");
}
