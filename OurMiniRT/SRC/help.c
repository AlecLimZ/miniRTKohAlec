/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 23:12:51 by Koh               #+#    #+#             */
/*   Updated: 2022/10/21 12:32:42 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	text(t_app *app, int h, int c, char *s)
{
	mlx_string_put(app->mlx_ptr, app->win_ptr, 8, h, c, s);
}

void	help(t_app *app)
{
	size_t		i;
	char *const	s[] = {
		"Object Control:",
		"  [T]Caption(Toggle)  [TAB]Next Object  [Hold Shift]Camera Shortcut",
		"  [Hold Ctrl]/[Hold Cmd(Mac)]Light Shortcut",
		"  [ARROWS]Movement  [I]Back  [O]Forward",
		"  [1]Light++  [2]Light--  [3]Radius++"
		"  [4]Radius--  [5]Height++  [6]Height--"
		"  [7]FOV++  [8]FOV--",
		"Render Toggles:",
		"  [J]Specular  [G]Gamma Correction  [K]Reflection"
		"  [L]Lighting  [N]Normal",
		"Misc:",
		"  [W]indowSize(Toggle)  [R]eload  [E]xport",
		"[H]Help(Toggle)"
	};

	mlx_clear_window(app->mlx_ptr, app->win_ptr);
	i = -1;
	while (++i < sizeof(s) / sizeof(*s))
		text(app, (i + 1) * 20, 0Xffff00, s[i]);
	if (app->features & FEATURE_NORMAL)
		text(app, ++i * 20, 0xffffff, "Thank You");
}
