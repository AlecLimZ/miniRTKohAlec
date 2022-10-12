/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 02:18:26 by Koh               #+#    #+#             */
/*   Updated: 2022/09/16 18:15:09 by Koh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// a scene may have none/multiple sphere/plane/cylinder
// these objects are malloc'ed and added to linked-list

// "pl <x,y,z> <orientation:x,y,z> <r,g,b>"
// eg "pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225"
bool	parse_plane(char *line, t_app *app)
{
	t_object *const	a = ft_calloc(1, sizeof(t_object));

	ft_lstadd_front(&app->objects, ft_lstnew(a));
	if (a)
		a->type = PLANE;
	if (a != NULL
		&& trim_str(&line, ft_isalpha) == 2
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_vec(&line, &a->coor, MIN_COOR, MAX_COOR) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_vec(&line, &a->orientation, -1, 1) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_rgb(&line, &a->color) == 1
		&& trim_str(&line, ft_isspace) >= 0
		&& (*line == '#' || *line == '\0'))
	{
		a->material = (t_material){{1, 0, 0}, 0, a->color};
		return (1);
	}
	return (0);
}

//  #define      IVORY {{0.9,  0.5, 0.1},   50., {{0.4, 0.4, 0.3}}}
//  #define RED_RUBBER {{1.4,  0.3, 0.0},   10., {{0.3, 0.1, 0.1}}}
//  #define     MIRROR {{0.0, 16.0, 0.8}, 1425., {{1.0, 1.0, 1.0}}}

// "sp <x,y,z> <diameter> <r,g,b>"
// eg "sp 0.0,0.0,20.6 12.6 10,0,255"
bool	parse_sphere(char *line, t_app *app)
{
	t_object *const	a = ft_calloc(1, sizeof(t_object));
	double			diameter;

	ft_lstadd_front(&app->objects, ft_lstnew(a));
	if (a)
		a->type = SPHERE;
	if (a != NULL
		&& trim_str(&line, ft_isalpha) == 2
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_vec(&line, &a->coor, MIN_COOR, MAX_COOR) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_nbr(&line, &diameter, 0, MAX_COOR) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_rgb(&line, &a->color) == 1
		&& trim_str(&line, ft_isspace) >= 0
		&& (*line == '#' || *line == '\0'))
	{
		a->radius = diameter / 2;
		a->material = (t_material){{0.9,  0.5, 0.1}, 50, a->color};
		return (true);
	}
	return (false);
}

// "cy <x,y,z> <orientation:x,y,z> <diameter> <height> <r,g,b>"
// eg "cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255"
bool	parse_cylinder(char *line, t_app *app)
{
	t_object *const	a = ft_calloc(1, sizeof(t_object));
	double			diameter;

	ft_lstadd_front(&app->objects, ft_lstnew(a));
	if (a)
		a->type = CYLINDER;
	if (a != NULL
		&& trim_str(&line, ft_isalpha) == 2
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_vec(&line, &a->coor, MIN_COOR, MAX_COOR) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_vec(&line, &a->orientation, -1, 1) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_nbr(&line, &diameter, 0, MAX_COOR) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_nbr(&line, &a->height, 0, MAX_COOR) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_rgb(&line, &a->color) == 1
		&& trim_str(&line, ft_isspace) >= 0
		&& (*line == '#' || *line == '\0'))
	{
		a->radius = diameter / 2;
		a->material = (t_material){{0.9,  0.5, 0.1}, 50, a->color};
		return (true);
	}
	return (false);
}

// "co <x,y,z> <orientation:x,y,z> <diameter> <height> <r,g,b>"
// eg "cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255"
bool	parse_cone_bonus(char *line, t_app *app)
{
	t_object *const	a = ft_calloc(1, sizeof(t_object));
	double			diameter;

	ft_lstadd_front(&app->objects, ft_lstnew(a));
	if (a)
		a->type = CONE;
	if (a != NULL
		&& trim_str(&line, ft_isalpha) == 2
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_vec(&line, &a->coor, MIN_COOR, MAX_COOR) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_vec(&line, &a->orientation, -1, 1) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_nbr(&line, &diameter, 0, MAX_COOR) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_nbr(&line, &a->height, 0, MAX_COOR) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_rgb(&line, &a->color) == 1
		&& trim_str(&line, ft_isspace) >= 0
		&& (*line == '#' || *line == '\0'))
	{
		a->radius = diameter / 2;
		a->material = (t_material){{0.9,  0.5, 0.1}, 50, a->color};
		return (true);
	}
	return (false);
}

// "C <x,y,z> <orientation:x,y,z> <FOV>" eg "C -50.0,0,20 0,0,1 70"
bool	parse_camera(char *line, t_app *app)
{
	t_object *const	a = ft_calloc(1, sizeof(t_object));

	ft_lstadd_front(&app->objects, ft_lstnew(a));
	if (a)
		a->type = CAMERA;
	app->camera = a;
	++app->camera_count;
	return (a != NULL
		&& trim_str(&line, ft_isalpha) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_vec(&line, &a->coor, MIN_COOR, MAX_COOR) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_vec(&line, &a->orientation, -1, 1) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_nbr(&line, &a->camera_fov, 0, 180) == 1
		&& trim_str(&line, ft_isspace) >= 0
		&& (*line == '#' || *line == '\0')
	);
}
