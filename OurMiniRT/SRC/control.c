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

static bool	is_movable(int type)
{
	return (type == CAMERA || type == LIGHT || type == LIGHT_BONUS
		|| type == SPHERE || type == PLANE || type == CYLINDER || type == CONE);
}

void	select_next(t_app *app)
{
	if (app->selected_object != NULL)
		app->selected_object = app->selected_object->next;
	if (app->selected_object == NULL)
		app->selected_object = app->objects;
	while (app->selected_object
		&& !is_movable(((t_object *)app->selected_object->content)->type))
			app->selected_object = app->selected_object->next;
	if (app->selected_object == NULL)
		select_next(app);
}
