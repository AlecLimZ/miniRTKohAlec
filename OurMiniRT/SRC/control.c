/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 23:12:51 by Koh               #+#    #+#             */
/*   Updated: 2022/10/21 13:46:55 by Koh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "key_codes.h"
#include <math.h>

static bool	gui_orientation(unsigned int key, t_object *c)
{
	if (c->type == CAMERA && (key == KEY_S || key == KEY_X))
		c->camera_rotation.x += pow(-1, key != KEY_S) * PI / 8;
	else if (c->type == CAMERA && (key == KEY_D || key == KEY_C))
		c->camera_rotation.y += pow(-1, key != KEY_D) * PI / 8;
	else if ((c->type == CYLINDER || c->type == PLANE) && key == KEY_S)
		c->orientation.x += 0.1f;
	else if ((c->type == CYLINDER || c->type == PLANE) && key == KEY_X)
		c->orientation.x -= 0.1f;
	else if ((c->type == CYLINDER || c->type == PLANE) && key == KEY_D)
		c->orientation.y += 0.1f;
	else if ((c->type == CYLINDER || c->type == PLANE) && key == KEY_C)
		c->orientation.y -= 0.1f;
	else if ((c->type == CYLINDER || c->type == PLANE) && key == KEY_F)
		c->orientation.z += 0.1f;
	else if ((c->type == CYLINDER || c->type == PLANE) && key == KEY_V)
		c->orientation.z -= 0.1f;
	else
		return (false);
	return (true);
}

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
	else if (key == KEY_ZERO)
		object->hide = !object->hide;
	else
		return (gui_orientation(key, object));
	return (true);
}

static bool	invalidate_input2(unsigned int key, t_app *app)
{
	if (app->keypressed & KEY_SHIFT_FLAG
		&& control_object(key, app->object[CAMERA]))
		;
	else if (app->keypressed & KEY_CTRL_FLAG
		&& control_object(key, app->object[LIGHT]))
		;
	else if (control_object(key, app->selected_object->content))
		;
	else
		return (false);
	return (true);
}

// todo: toggle FEATURE_CAPTION, should redraw instead of re-render
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
			create_window(app, ALT_WINDOW_WIDTH, ALT_WINDOW_HEIGHT);
		else
			create_window(app, WINDOW_WIDTH, WINDOW_HEIGHT);
	}
	else if (!invalidate_input2(key, app))
	{
		printf("unknown key pressed: %d\n", key);
		return ;
	}
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
		select_next(app, NULL);
	else
		invalidate_input(key, app);
	return (0);
}
