/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:33:51 by leng-chu          #+#    #+#             */
/*   Updated: 2022/09/16 19:31:28 by Koh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ft_pixel(int *px, int xy, int color)
{
	px[xy] = color;
}

static void	init_app(t_app *app)
{
	*app = (t_app){};
}

static void	load_scene_or_exit(t_app *app, char *filepath)
{
	parse_file(filepath, app);
	printf("lstsize %d\n", ft_lstsize(app->objects));
}

static void	start_gui(t_app *app)
{
	char	*input;

	ft_putstr_fd("Your name: ", 1);
	if (get_next_line(0, &input))
	{
		ft_putstr_fd("Hello ", 1);
		ft_putendl_fd(input, 1);
		free(input);
	}
	app->mlx_ptr = if_null_exit(mlx_init(), app);
	app->win_ptr = mlx_new_window(app->mlx_ptr, 1000, 500, "HELLO");
	app->image.ptr = mlx_new_image(app->mlx_ptr, 300, 300);
	app->image.px = (int *)mlx_get_data_addr(
			app->image.ptr, &app->image.bits_per_pixel,
			&app->image.line_length, &app->image.endian);
	for (int i = 0; i < 300; i++)
		for (int j = 0; j < 300; j++)
			ft_pixel(app->image.px, i * 300 + j, 0x00FF0000);
	mlx_put_image_to_window(app->mlx_ptr, app->win_ptr, app->image.ptr, 100, 0);
	mlx_do_key_autorepeaton(app->mlx_ptr);
	mlx_hook(app->win_ptr, 17, 1L << 17, &gui_exit, app);
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
