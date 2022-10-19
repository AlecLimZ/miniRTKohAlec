/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 23:12:51 by Koh               #+#    #+#             */
/*   Updated: 2022/10/11 23:16:33 by Koh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdio.h>

static int	ft_checklight(const t_object *object)
{
	return (object->type == AMBIENT
		|| object->type == LIGHT
		|| object->type == LIGHT_BONUS);
}

static void	adjust_val(float *value, float step, float lo, float hi)
{
	*value = clamp(*value + step, lo, hi);
}

static bool	control_object(unsigned int key, t_object *object)
{
	if (key == KEY_I || key == KEY_O)
		object->coor.z += add_or_minus(key == KEY_I, 0.5f);
	else if (key == KEY_UP || key == KEY_DOWN)
		object->coor.y += add_or_minus(key == KEY_UP, 0.5f);
	else if (key == KEY_RIGHT || key == KEY_LEFT)
		object->coor.x += add_or_minus(key == KEY_RIGHT, 0.5f);
	else if (ft_checklight(object) && (key == KEY_TWO || key == KEY_ONE))
		adjust_val(&object->light_brightness,
			add_or_minus(key == KEY_ONE, 0.1f), 0.0f, 1.0f);
	else if (!ft_checklight(object) && (key == KEY_THREE || key == KEY_FOUR))
		adjust_val(&object->radius,
			add_or_minus(key == KEY_THREE, 0.5f), 0.0f, 1000.0f);
	else if (key == KEY_FIVE || key == KEY_SIX)
		adjust_val(&object->height,
			add_or_minus(key == KEY_FIVE, 0.5f), 0.0f, 1000.0f);
	else if (object->type == CAMERA && (key == KEY_SEVEN || key == KEY_EIGHT))
		adjust_val(&object->camera_fov,
			add_or_minus(key == KEY_SEVEN, 10.0f), 0.0f, 180.0f);
	else
		return (false);
	return (true);
}

static void	invalidate_input(unsigned int key, t_app *app)
{
	if (key == KEY_R)
		reload_scene(app);
	else if (key == KEY_W && ++app->mini)
		create_window(
			app, 600 + (app->mini & 1) * 1000, 340 + (app->mini & 1) * 560);
	else if (key == KEY_G)
		app->use_gamma_correction = !app->use_gamma_correction;
	else if (key == KEY_Y)
		app->render_mode = (app->render_mode + 1) % RENDER_MODE_END;
	else if (key == KEY_S || key == KEY_X)
		app->object_ptr[CAMERA]->orientation.x
			+= add_or_minus(key == KEY_S, PI / 8);
	else if (key == KEY_D || key == KEY_C)
		app->object_ptr[CAMERA]->orientation.y
			+= add_or_minus(key == KEY_D, PI / 8);
	else if (key == KEY_F || key == KEY_V)
		app->object_ptr[CAMERA]->orientation.z
			+= add_or_minus(key == KEY_F, PI / 8);
	else if (!control_object(key, app->selected_object->content))
	{
		printf("unknown key %d\n", key);
		return ;
	}
	++app->invalidated;
}

int	gui_input(unsigned int key, t_app *app)
{
	if (key == KEY_ESC)
		app_exit(app, NULL);
	else if (key == KEY_E)
		export_scene(app->objects);
	else if (key == KEY_TAB)
	{
		select_next(app);
		mlx_put_image_to_window(
			app->mlx_ptr, app->win_ptr, app->image.ptr, 0, 0);
		mlx_string_put(app->mlx_ptr, app->win_ptr, 24, 24, 0XFFFF00,
			(char *)get_object_typename(app->selected_object->content));
	}
	else
		invalidate_input(key, app);
	return (0);
}
