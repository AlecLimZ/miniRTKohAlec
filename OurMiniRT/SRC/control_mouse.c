/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_mouse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 23:12:51 by Koh               #+#    #+#             */
/*   Updated: 2022/10/21 11:59:48 by leng-chu         ###   ########.fr       */
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

int	gui_mousedown(int button, int x, int y, t_app *app)
{
	const float		fov = (app->object[CAMERA]->camera_fov * PI / 180);
	t_vec3			dir;
	t_hitpayload	payload;
	t_list			*list;

	list = NULL;
	if (button != MOUSE_BUTTON_LEFT)
		return (0);
	dir.x = (x + 0.5f) - app->image.width / 2.f;
	dir.y = -(y + 0.5f) + app->image.height / 2.f;
	dir.z = -app->image.height / (2.f * tan(fov / 2.f));
	dir = look_at(dir, app->object[CAMERA]->orientation);
	rotate_x(&dir.y, &dir.z, app->object[CAMERA]->camera_rotation.x);
	rotate_y(&dir.x, &dir.z, app->object[CAMERA]->camera_rotation.y);
	payload = scene_intersect(app->object[CAMERA]->coor,
			normalized(dir), app->objects);
	if (payload.hit && payload.object)
		list = search_list(app->objects, payload.object);
	if (!list)
		list = search_list(app->objects, app->object[AMBIENT]);
	select_next(app, list);
	print_object(app->selected_object->content);
	return (0);
}
