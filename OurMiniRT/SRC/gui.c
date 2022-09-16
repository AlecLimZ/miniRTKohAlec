/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 19:17:26 by Koh               #+#    #+#             */
/*   Updated: 2022/09/16 19:31:12 by Koh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	gui_input(int key, t_app *app)
{
	static const char	map[] = {
	[KEY_A] = 0, [KEY_B] = 1, [KEY_C] = 2, [KEY_D] = 3
	};

	(void)app;
	printf("user input %c\n", 'A' + map[key]);
	return (0);
}

int	gui_render(t_app *app)
{
	(void)app;
	return (0);
}
