/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 19:17:26 by Koh               #+#    #+#             */
/*   Updated: 2022/09/16 22:26:05 by Koh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	gui_input(unsigned int key, t_app *app)
{
	static const char	map[127] = {
	[KEY_ONE] = '1', [KEY_TWO] = '2', [KEY_THREE] = '3', [KEY_FOUR] = '4',
	[KEY_FIVE] = '5', [KEY_SIX] = '6', [KEY_SEVEN] = '7', [KEY_EIGHT] = '8',
	[KEY_NINE] = '9', [KEY_ZERO] = '0',
	[KEY_A] = 'a', [KEY_B] = 'b', [KEY_C] = 'c', [KEY_D] = 'd', [KEY_E] = 'e',
	[KEY_F] = 'f', [KEY_G] = 'g', [KEY_H] = 'h', [KEY_I] = 'i', [KEY_J] = 'j',
	[KEY_K] = 'k', [KEY_L] = 'l', [KEY_M] = 'm', [KEY_N] = 'n', [KEY_O] = 'o',
	[KEY_P] = 'p', [KEY_Q] = 'q', [KEY_R] = 'r', [KEY_S] = 's', [KEY_T] = 't',
	[KEY_U] = 'u', [KEY_V] = 'v', [KEY_W] = 'w', [KEY_X] = 'x', [KEY_Y] = 'y',
	[KEY_Z] = 'z' };

	if (key == KEY_ESC)
		app_exit(app, NULL);
	if (key == KEY_UP)
		app->y++;
	else if (key == KEY_DOWN)
		app->y--;
	else if (key == KEY_LEFT)
		app->x++;
	else if (key == KEY_RIGHT)
		app->x--;
	else if (key < 127)
		ft_putchar_fd(map[key], 1);
	app->last_updated++;
	return (0);
}

static inline int	color(double r, double g, double b)
{
	return (((int)r << 16) + ((int)g << 8) + (int)b);
}

		// if (last_updated + 1 < app->last_updated)
		// 	printf("skipped %d render\n", app->last_updated - last_updated - 1);
int	gui_render(t_app *app)
{
	static unsigned int	last_updated = 0;
	int					w;
	int					h;
	t_vec3				v;

	if (last_updated < app->last_updated)
	{
		v.r = 255.999 / (app->width - 1);
		v.g = 255.999 / (app->height - 1);
		v.b = 255.999 * .25;
		last_updated = app->last_updated;
		h = -1;
		while (++h < app->height)
		{
			w = -1;
			while (++w < app->width)
				app->image.px[h * app->width + w]
					= color(w * v.r, (app->height - 1 - h) * v.g, v.b);
		}
		mlx_clear_window(app->mlx_ptr, app->win_ptr);
		mlx_put_image_to_window(
			app->mlx_ptr, app->win_ptr, app->image.ptr, app->x, app->y);
	}
	return (0);
}
