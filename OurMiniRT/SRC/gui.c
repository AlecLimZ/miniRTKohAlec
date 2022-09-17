/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 19:17:26 by Koh               #+#    #+#             */
/*   Updated: 2022/09/17 10:01:02 by Koh              ###   ########.fr       */
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

static void	*gradient(t_app *app)
{
	const double	r = 255.999 / (app->width - 1);
	const double	g = 255.999 / (app->height - 1);
	const double	b = 255.999 * .25;
	t_wh			size;

	size.h = -1;
	while (++size.h < app->height)
	{
		size.w = -1;
		while (++size.w < app->width)
			app->image.px[size.h * app->width + size.w]
				= color(size.w * r, (app->height - 1 - size.h) * g, b);
	}
	return (app->image.ptr);
}

// todo: not just x86 little-endian [b,g,r,a]
static void	*ants(t_app *app)
{
	const int	fd = open("/dev/random", 0);
	int			i;

	ft_bzero(app->image.addr, app->width * app->height * 4);
	i = app->width * app->height;
	while (i--)
		read(fd, (void *)app->image.c + i * 4, 3);
	return (app->image.ptr);
}

int	gui_render(t_app *app)
{
	static unsigned int		last_updated = 0;
	static unsigned long	tick = 0;

	++tick;
	if (last_updated < app->last_updated)
	{
		printf("tick %lu\n", tick);
		last_updated = app->last_updated;
		mlx_clear_window(app->mlx_ptr, app->win_ptr);
		mlx_put_image_to_window(
			app->mlx_ptr, app->win_ptr, gradient(app), app->x, app->y);
	}
	else if (tick % 1000 == 0)
	{
		mlx_put_image_to_window(
			app->mlx_ptr, app->win_ptr, ants(app), app->x, app->y);
	}
	return (0);
}
