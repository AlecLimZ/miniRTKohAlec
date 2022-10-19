/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 13:10:51 by Koh               #+#    #+#             */
/*   Updated: 2022/10/13 14:19:14 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// a scene must have only 1 ambient, camera, light. they are stored in struct
// "A <ratio> <r,g,b>" eg "A 0.2 255,255,25"
t_object	parse_ambient(char *line)
{
	t_object	a;

	a = (t_object){.type = OBJECT_TYPE_ERROR};
	if (line != NULL
		&& trim_chr(&line, 'A') == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_nbr(&line, &a.ambient_ratio, 0, 1) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_rgb(&line, &a.color) == 1
		&& trim_str(&line, ft_isspace) >= 0
		&& (*line == '#' || *line == '\0'))
	{
		a.type = AMBIENT;
	}
	return (a);
}

// "L <x,y,z> <brightness> <r,g,b>" eg "L -40.0,50.0,0.0 0.6 10,0,255"
t_object	parse_light(char *line)
{
	t_object	a;

	a = (t_object){.type = OBJECT_TYPE_ERROR};
	if (line != NULL
		&& trim_chr(&line, 'L') == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_vec(&line, &a.coor, MIN_COOR, MAX_COOR) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_nbr(&line, &a.light_brightness, 0, 1) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_rgb(&line, &a.color) == 1
		&& trim_str(&line, ft_isspace) >= 0
		&& (*line == '#' || *line == '\0'))
	{
		a.type = LIGHT;
	}
	return (a);
}

// "li <x,y,z> <brightness> <r,g,b>" eg "L -40.0,50.0,0.0 0.6 10,0,255"
t_object	parse_light_bonus(char *line)
{
	t_object	a;

	a = (t_object){.type = OBJECT_TYPE_ERROR};
	if (line != NULL
		&& trim_chr(&line, 'l') == 1
		&& trim_chr(&line, 'i') == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_vec(&line, &a.coor, MIN_COOR, MAX_COOR) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_nbr(&line, &a.light_brightness, 0, 1) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_rgb(&line, &a.color) == 1
		&& trim_str(&line, ft_isspace) >= 0
		&& (*line == '#' || *line == '\0'))
	{
		a.type = LIGHT_BONUS;
	}
	return (a);
}
