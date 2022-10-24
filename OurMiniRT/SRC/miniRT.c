/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 11:33:51 by leng-chu          #+#    #+#             */
/*   Updated: 2022/10/21 12:33:38 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "ansi_colors.h"

// init_app is required before app_exit
static void	init_app(t_app *app)
{
	*app = (t_app){
		.features = FEATURE_LIGHT};
}

static void	load_scene_or_exit(t_app *app, char *filepath)
{
	app->scene_file = filepath;
	parse_file(filepath, app);
	select_next(app, app->objects);
}

void	reload_scene(t_app *app)
{
	ft_lstclear(&app->objects, free);
	ft_bzero(app->object_count, sizeof(app->object_count));
	parse_file(app->scene_file, app);
	select_next(app, app->objects);
}

int	main(int argc, char **argv)
{
	t_app		app;

	init_app(&app);
	if (argc != 2)
		app_exit(&app, "Require 1 rt file");
	load_scene_or_exit(&app, argv[1]);
	if (WINDOW_WIDTH < ALT_WINDOW_WIDTH)
		ft_putendl_fd(LIGHT_RED_BG LIGHT_YELLOW
			"Address sanitizer is enabled. Performance is affected."
			RESET, 2);
	start_gui(&app, WINDOW_WIDTH, WINDOW_HEIGHT);
	app_exit(&app, "Unexpected GUI failure");
}
