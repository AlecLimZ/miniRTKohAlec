/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 02:18:26 by Koh               #+#    #+#             */
/*   Updated: 2022/10/19 13:15:51 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "raytracer.h"

// a scene may have none/multiple sphere/plane/cylinder
// these objects are malloc'ed and added to linked-list

// "pl <x,y,z> <orientation:x,y,z> <r,g,b>"
// eg "pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225"
t_object	parse_plane(char *line)
{
	t_object	a;

	a = (t_object){.type = OBJECT_TYPE_ERROR};
	if (line != NULL
		&& trim_chr(&line, 'p') == 1
		&& trim_chr(&line, 'l') == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_vec(&line, &a.coor, MIN_COOR, MAX_COOR) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_vec(&line, &a.orientation, -1, 1) == 1
		&& norm(a.orientation) > 0
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_rgb(&line, &a.color) == 1
		&& trim_str(&line, ft_isspace) >= 0
		&& (*line == '#' || *line == '\0'))
	{
		a.type = PLANE;
		a.material = (t_material){{1, 0, 0}, 0, a.color};
		a.orientation = normalized(a.orientation);
	}
	return (a);
}

// "sp <x,y,z> <diameter> <r,g,b>"
// eg "sp 0.0,0.0,20.6 12.6 10,0,255"
t_object	parse_sphere(char *line)
{
	t_object	a;

	a = (t_object){.type = OBJECT_TYPE_ERROR};
	if (line != NULL
		&& trim_chr(&line, 's') == 1
		&& trim_chr(&line, 'p') == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_vec(&line, &a.coor, MIN_COOR, MAX_COOR) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_nbr(&line, &a.radius, 0, MAX_COOR) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_rgb(&line, &a.color) == 1
		&& trim_str(&line, ft_isspace) >= 0
		&& (*line == '#' || *line == '\0'))
	{
		a.type = SPHERE;
		a.radius /= 2;
		a.material = (t_material){{0.9, 0.5, 0.1}, 50, a.color};
	}
	return (a);
}

// "cy <x,y,z> <orientation:x,y,z> <diameter> <height> <r,g,b>"
// eg "cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255"
t_object	parse_cylinder(char *line)
{
	t_object	a;

	a = (t_object){.type = OBJECT_TYPE_ERROR};
	if (line != NULL
		&& trim_chr(&line, 'c') == 1
		&& trim_chr(&line, 'y') == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_vec(&line, &a.coor, MIN_COOR, MAX_COOR) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_vec(&line, &a.orientation, -1, 1) == 1
		&& norm(a.orientation) > 0
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_nbr(&line, &a.radius, 0, MAX_COOR) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_nbr(&line, &a.height, 0, MAX_COOR) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_rgb(&line, &a.color) == 1
		&& trim_str(&line, ft_isspace) >= 0
		&& (*line == '#' || *line == '\0'))
	{
		a.type = CYLINDER;
		a.radius /= 2;
		a.material = (t_material){{0.9, 0.5, 0.1}, 50, a.color};
	}
	return (a);
}

// "co <x,y,z> <orientation:x,y,z> <diameter> <height> <r,g,b>"
// eg "cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255"
t_object	parse_cone_bonus(char *line)
{
	t_object	a;

	a = (t_object){.type = OBJECT_TYPE_ERROR};
	if (line != NULL
		&& trim_chr(&line, 'c') == 1
		&& trim_chr(&line, 'o') == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_vec(&line, &a.coor, MIN_COOR, MAX_COOR) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_vec(&line, &a.orientation, -1, 1) == 1
		&& norm(a.orientation) > 0
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_nbr(&line, &a.radius, 0, MAX_COOR) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_nbr(&line, &a.height, 0, MAX_COOR) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_rgb(&line, &a.color) == 1
		&& trim_str(&line, ft_isspace) >= 0
		&& (*line == '#' || *line == '\0'))
	{
		a.type = CONE;
		a.radius /= 2;
		a.material = (t_material){{0.9, 0.5, 0.1}, 50, a.color};
	}
	return (a);
}

// "C <x,y,z> <orientation:x,y,z> <FOV>" eg "C -50.0,0,20 0,0,1 70"
t_object	parse_camera(char *line)
{
	t_object	a;

	a = (t_object){.type = OBJECT_TYPE_ERROR};
	if (line != NULL
		&& trim_chr(&line, 'C') == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_vec(&line, &a.coor, MIN_COOR, MAX_COOR) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_vec(&line, &a.orientation, -1, 1) == 1
		&& norm(a.orientation) > 0
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_nbr(&line, &a.camera_fov, 0, 180) == 1
		&& trim_str(&line, ft_isspace) >= 0
		&& (*line == '#' || *line == '\0'))
	{
		a.type = CAMERA;
	}
	return (a);
}
