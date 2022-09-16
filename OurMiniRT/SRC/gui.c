/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 19:17:26 by Koh               #+#    #+#             */
/*   Updated: 2022/09/16 19:57:20 by Koh              ###   ########.fr       */
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
	[KEY_Z] = 'z',
	};

	if (key == KEY_ESC)
		app_exit(app, NULL);
	if (key < 127)
		printf("user input %c\n", 'A' + map[key]);
	return (0);
}

int	gui_render(t_app *app)
{
	(void)app;
	return (0);
}
