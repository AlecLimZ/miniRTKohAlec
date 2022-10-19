/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:19:34 by Koh               #+#    #+#             */
/*   Updated: 2022/10/19 18:20:03 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>
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
	//o->type == CAMERA ||
	else if (o->type == PLANE || o->type == CYLINDER || o->type == CONE)
		o->orientation = normalized(o->orientation);
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
		rotate_x(&dir.y, &dir.z, app->object[CAMERA]->orientation.x);
		rotate_y(&dir.x, &dir.z, app->object[CAMERA]->orientation.y);
		rotate_z(&dir.x, &dir.y, app->object[CAMERA]->orientation.z);
		app->image.px[pix] = to_rgb(
				cast_ray(app->object[CAMERA]->coor,
					normalized(dir), 0, app),
				app->features & FEATURE_GAMMA_CORRECTION);
	}
	return (app->image.ptr);
}

// float smootherstep(float edge0, float edge1, float x) {
//   // Scale, and clamp x to 0..1 range
//   x = clamp((x - edge0) / (edge1 - edge0), 0.0, 1.0);
//   // Evaluate polynomial
//   return x * x * x * (x * (x * 6 - 15) + 10);
// }
