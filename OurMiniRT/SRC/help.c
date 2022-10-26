/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 23:12:51 by Koh               #+#    #+#             */
/*   Updated: 2022/10/25 07:33:31 by Koh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	text(t_app *app, int h, int c, char *s)
{
	mlx_string_put(app->mlx_ptr, app->win_ptr, 16, h, c, s);
}

void	help(t_app *app)
{
	size_t		i;
	char *const	s[] = {
		"Object Control:",
		"  [T]Caption(Toggle)  [Click]Select Object  [TAB]Next Object",
		"  Shortcuts: [Hold Shift]Camera  [Hold Ctrl]/[Hold Cmd(Mac)]Light",
		"  Movements: [Up]Y++  [Down]Y--  [Left]X--  [Right]X++"
		"  [I]Z--  [O]Z++",
		"  Camera Rotations: [S/X]Around X  [D/C]Around Y",
		"  Object Orientation: [S/X]X  [D/C]Y  [F/C]Z  ",
		"  Amibient/Light: [1]Brightness++  [2]Brightness--  ",
		"  Sphere/Cylinder: [3]Radius++   [4]Radius--",
		"  Cylinder: [5]Height++  [6]Height--", "  Camera: [7]FOV++  [8]FOV--",
		"  Cylinder/Plane/Sphere: [9]Checkerboard(toggle)",
		"  [0]Hide(toggle)", "  [Ctrl/Cmd + Click]Clone Object",
		"Render Toggles:", "  [J]Specular  [G]Gamma Correction  [K]Reflection",
		"  [L]Lighting  [N]Normal  [W]indow Size(Toggle)",
		"Data:", "  [R]eload  [E]xport(Print)  [Q]Log(Toggle)", "[H]Help(Toggle)"
	};

	mlx_clear_window(app->mlx_ptr, app->win_ptr);
	i = -1;
	while (++i < sizeof(s) / sizeof(*s))
		text(app, (i + 1) * 24, 0Xffff00, s[i]);
	if (app->features & FEATURE_NORMAL)
		text(app, ++i * 24, 0xffffff, "Thank You");
}
