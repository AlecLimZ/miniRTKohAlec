/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 19:17:26 by Koh               #+#    #+#             */
/*   Updated: 2022/10/11 23:26:47 by Koh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include "miniRT.h"

int	gui_input(unsigned int key, t_app *app)
{
	if (key == KEY_ESC)
		app_exit(app, NULL);
	else if (key == KEY_TAB)
		select_next(app);
	else if (key == KEY_A || key == KEY_Z)
		((t_object *)app->selected_object->content)->coor.z
			+= pow(-1, key != KEY_A);
	else if (key == KEY_UP || key == KEY_DOWN)
		((t_object *)app->selected_object->content)->coor.y
			+= pow(-1, key != KEY_UP);
	else if (key == KEY_RIGHT || key == KEY_LEFT)
		((t_object *)app->selected_object->content)->coor.x
			+= pow(-1, key != KEY_RIGHT);
	else if (key == KEY_S || key == KEY_X)
		app->camera->orientation.x += pow(-1, key != KEY_S) * PI * 2 / 8;
	else if (key == KEY_D || key == KEY_C)
		app->camera->orientation.y += pow(-1, key != KEY_D) * PI * 2 / 8;
	else if (key == KEY_F || key == KEY_V)
		app->camera->orientation.z += pow(-1, key != KEY_F) * PI * 2 / 8;
	else if (key == KEY_N)
		app->render_mode = (app->render_mode + 1) % RENDER_MODE_END;
	++app->last_updated;
	return (0);
}

// float dir_x=0,dir_y=0,dir_z= +-1;
// rotate_x(&dir_y, &dir_z, app->camera->orientation.x);
// rotate_y(&dir_x, &dir_z, app->camera->orientation.y);
// rotate_z(&dir_x, &dir_y, app->camera->orientation.z);
// app->camera->coor.x += dir_x;
// app->camera->coor.y += dir_y;
// app->camera->coor.z += dir_z;

int	gui_render(t_app *app)
{
	static unsigned int		last_updated = 0;
	const clock_t			begin = clock();
	const char *const		name[] = {
	[CAMERA] = "Camera", [LIGHT] = "Light",
	[SPHERE] = "Sphere", [PLANE] = "Plane", [CYLINDER] = "Cylinder",
	[CONE] = "Cone", [LIGHT_BONUS] = "Light bonus"};

	if (last_updated < app->last_updated)
	{
		last_updated = app->last_updated;
		mlx_put_image_to_window(
			app->mlx_ptr, app->win_ptr, raytrace(app), 0, 0);
		printf("raytracing %fs\n", (double)(clock() - begin) / CLOCKS_PER_SEC);
		mlx_string_put(app->mlx_ptr, app->win_ptr, 24, 24, 0XFFFF00,
			(char *)name[((t_object *)app->selected_object->content)->type]);
		mlx_string_put(app->mlx_ptr, app->win_ptr, 24, app->height - 30,
			0xFFFF00,
			"TAB=Next_Object  UP=Move_Y+  DOWN=Move_Y-  LEFT=Move_X-  "
			"RIGHT=Move_X+  A=Move_Z+  Z=Move_Z-  N=Toggle_Render");
	}
	return (0);
}
