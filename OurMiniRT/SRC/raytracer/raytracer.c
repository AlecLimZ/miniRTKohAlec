/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:19:34 by Koh               #+#    #+#             */
/*   Updated: 2022/10/24 12:54:52 by Koh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>
#include <float.h>
#include "raytracer.h"

// gamma correction 1/2.2 == 0.4545
static int	to_rgb(t_vec3 color, bool use_gamma_correction)
{
	float	max;

	if (use_gamma_correction)
	{
		color.x = pow(color.x, 0.4545);
		color.y = pow(color.y, 0.4545);
		color.z = pow(color.z, 0.4545);
	}
	max = fmax(1.f, fmax(color.x, fmax(color.y, color.z)));
	return (((int)(255.999 * color.x / max) << 16)
		+ ((int)(255.999 * color.y / max) << 8)
		+ (int)(255.999 * color.z / max));
}

static void	cal_color_and_orient(void *content)
{
	t_object *const	o = content;

	if (o->type == AMBIENT || o->type == LIGHT || o->type == LIGHT_BONUS)
		o->light_color = mulvf(o->color, o->light_brightness);
	else if (o->type == PLANE || o->type == CYLINDER || o->type == CONE
		|| o->type == CAMERA)
		o->orientation = normalized(o->orientation);
}

//normalized(orientation) = normalized(from - to);
t_vec3	look_at(t_vec3 dir, t_vec3 orientation)
{
	const t_vec3	forward = orientation;
	t_vec3			right;
	t_vec3			up;
	t_vec3			rotated;

	up = (t_vec3){{0, 1, 0}};
	if (1.0f - forward.y < FLT_EPSILON)
		right = (t_vec3){{1, 0, 0}};
	else if (forward.y + 1.0f < FLT_EPSILON)
		right = (t_vec3){{-1, 0, 0}};
	else
		right = normalized(cross(up, forward));
	up = cross(forward, right);
	dir.x = -dir.x;
	dir.z = -dir.z;
	rotated.x = dir.x * right.x + dir.y * up.x + dir.z * forward.x;
	rotated.y = dir.x * right.y + dir.y * up.y + dir.z * forward.y;
	rotated.z = dir.x * right.z + dir.y * up.z + dir.z * forward.z;
	return (rotated);
}

void	*raytrace(const t_app *app)
{
	const int	width = app->image.width;
	const int	height = app->image.height;
	const float	fov = (app->object[CAMERA]->camera_fov * PI / 180);
	t_vec3		dir;
	int			pix;

	ft_lstiter(app->objects, cal_color_and_orient);
	pix = -1;
	while (++pix < width * height)
	{
		dir.x = +(pix % width + 0.5f) - width / 2.f;
		dir.y = -(pix / width + 0.5f) + height / 2.f;
		dir.z = -height / (2.f * tan(fov / 2.f));
		dir = look_at(dir, app->object[CAMERA]->orientation);
		rotate_x(&dir.y, &dir.z, app->object[CAMERA]->camera_rotation.x);
		rotate_y(&dir.x, &dir.z, app->object[CAMERA]->camera_rotation.y);
		app->image.px[pix] = to_rgb(
				cast_ray(app->object[CAMERA]->coor,
					normalized(dir), 0, app),
				app->features & FEATURE_GAMMA_CORRECTION);
	}
	return (app->image.ptr);
}
