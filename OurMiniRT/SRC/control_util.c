/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 23:12:51 by Koh               #+#    #+#             */
/*   Updated: 2022/10/11 23:16:33 by Koh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stddef.h>
#include "key_codes.h"


float	clamp(float value, float lo, float hi)
{
	if (value < lo)
		return (lo);
	if (value > hi)
		return (hi);
	return (value);
}

t_object	*as_object(const t_list *p)
{
	return (p->content);
}

void	select_next(t_app *app)
{
	if (app->selected_object != NULL)
		app->selected_object = app->selected_object->next;
	if (app->selected_object == NULL)
		app->selected_object = app->objects;
}

float	add_or_minus(int add_condition, float step)
{
	if (add_condition)
		return (step);
	else
		return (-step);
}

int gui_keyup(int keycode, t_app *app)
{
	if (keycode == KEY_SHIFT)
		app->keypressed &= ~KEY_SHIFT_FLAG;
	else if (keycode == KEY_CTRL)
		app->keypressed &= ~KEY_CTRL_FLAG;
	return (0);
}
