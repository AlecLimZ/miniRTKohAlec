/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 23:12:51 by Koh               #+#    #+#             */
/*   Updated: 2022/10/21 12:30:30 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "key_codes.h"

static bool	control_object(unsigned int key, t_object *object)
{
	if (key == KEY_I || key == KEY_O)
		object->coor.z += add_or_minus(key == KEY_I, 0.5f);
	else if (key == KEY_UP || key == KEY_DOWN)
		object->coor.y += add_or_minus(key == KEY_UP, 0.5f);
	else if (key == KEY_RIGHT || key == KEY_LEFT)
		object->coor.x += add_or_minus(key == KEY_RIGHT, 0.5f);
	else if (ft_checklight(object) && (key == KEY_ONE || key == KEY_TWO))
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

static void	invalidate_input2(unsigned int key, t_app *app)
{
	if (key == KEY_S || key == KEY_X)
		app->object[CAMERA]->orientation.x
			+= add_or_minus(key == KEY_S, ROT);
	else if (key == KEY_D || key == KEY_C)
		app->object[CAMERA]->orientation.y
			+= add_or_minus(key == KEY_D, PI / 8);
	else if (key == KEY_F || key == KEY_V)
		app->object[CAMERA]->orientation.z
			+= add_or_minus(key == KEY_F, PI / 8);
	else if (app->keypressed & KEY_SHIFT_FLAG
		&& control_object(key, app->object[CAMERA]))
		;
	else if (app->keypressed & KEY_CTRL_FLAG
		&& control_object(key, app->object[LIGHT]))
		;
	else if (!control_object(key, app->selected_object->content))
		return ((void)printf("unknown key pressed: %d\n", key));
}

static void	invalidate_input(unsigned int key, t_app *app)
{
	const int	toggles[] = {
	[KEY_G] = FEATURE_GAMMA_CORRECTION, [KEY_H] = FEATURE_HELP,
	[KEY_J] = FEATURE_SPECULAR, [KEY_K] = FEATURE_REFLECTION,
	[KEY_L] = FEATURE_LIGHT, [KEY_N] = FEATURE_NORMAL,
	[KEY_T] = FEATURE_CAPTION, };

	if (key < sizeof(toggles) / sizeof(*toggles) && toggles[key])
		app->features ^= toggles[key];
	else if (key == KEY_R)
		reload_scene(app);
	else if (key == KEY_W)
	{
		app->features ^= FEATURE_SMALLER_WINDOW;
		if (app->features & FEATURE_SMALLER_WINDOW)
			create_window(app, SMALL_WINDOW_WIDTH, SMALL_WINDOW_HEIGHT);
		else
			create_window(app, WINDOW_WIDTH, WINDOW_HEIGHT);
	}
	else
		invalidate_input2(key, app);
	++app->invalidated;
}

int	gui_keydown(unsigned int key, t_app *app)
{
	if (key == KEY_ESC)
		app_exit(app, NULL);
	else if (key == KEY_E)
		export_scene(app->objects);
	else if (key == KEY_SHIFT)
		app->keypressed |= KEY_SHIFT_FLAG;
	else if (key == KEY_CTRL)
		app->keypressed |= KEY_CTRL_FLAG;
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
