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
#include "raytracer.h"
#include "key_codes.h"
#include <stdio.h>

static t_list	*search_list(t_list *list, const t_object *o)
{
	while (list)
	{
		if (list->content == o)
			return (list);
		list = list->next;
	}
	return (NULL);
}

int	gui_mouseup(int button, int x, int y, t_app *app)
{
	const float		fov = (app->object[CAMERA]->camera_fov * PI / 180);
	t_vec3			dir;
	t_hitpayload	payload;
	t_list			*list;

	if (button != MOUSE_BUTTON_LEFT)
		return (0);
	dir.x = (x + 0.5f) - app->image.width / 2.f;
	dir.y = -(y + 0.5f) + app->image.height / 2.f;
	dir.z = -app->image.height / (2.f * tan(fov / 2.f));
	rotate_x(&dir.y, &dir.z, app->object[CAMERA]->orientation.x);
	rotate_y(&dir.x, &dir.z, app->object[CAMERA]->orientation.y);
	rotate_z(&dir.x, &dir.y, app->object[CAMERA]->orientation.z);
	payload = scene_intersect(app->object[CAMERA]->coor, normalized(dir), app->objects);
	if (payload.hit && payload.object)
		list = search_list(app->objects, payload.object);
	if (!list)
		list = search_list(app->objects, app->object[AMBIENT]);
	if (list)
	{
		app->selected_object = list;
		++app->invalidated;
	}
	return (0);
}
