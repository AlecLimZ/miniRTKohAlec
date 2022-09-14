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

// "sp <x,y,z> <diameter> <r,g,b>" eg "sp 0.0,0.0,20.6 12.6 10,0,255"
int	parse_sphere(char *line, t_app *app)
{
	t_object *const	a = ft_calloc(1, sizeof(t_object));

	if (a != NULL
		&& trim_str(&line, ft_isalpha) == 2
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_vec(&line, &a->coor, MIN_COOR, MAX_COOR) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_nbr(&line, &a->diameter, 0, MAX_COOR) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_rgb(&line, &a->color) == 1
		&& trim_str(&line, ft_isspace) >= 0
		&& (*line == '#' || *line == '\0'))
	{
		a->type = SPHERE;
		ft_lstadd_front(&app->objects, ft_lstnew(a));
		return (1);
	}
	return (0);
}

// "pl <x,y,z> <orientation:x,y,z> <r,g,b>"
// eg "pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225"
int	parse_plane(char *line, t_app *app)
{
	t_object *const	a = ft_calloc(1, sizeof(t_object));

	if (a != NULL
		&& trim_str(&line, ft_isalpha) == 2
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_vec(&line, &a->coor, MIN_COOR, MAX_COOR) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_vec(&line, &a->orientation, -1, 1) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_rgb(&line, &a->color) == 1
		&& trim_str(&line, ft_isspace) >= 0 && (*line == '#' || *line == '\0'))
	{
		a->type = PLANE;
		ft_lstadd_front(&app->objects, ft_lstnew(a));
		return (1);
	}
	return (0);
}

// "cy <x,y,z> <orientation:x,y,z> <diameter> <height> <r,g,b>"
// eg "cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255"
int	parse_cylinder(char *line, t_app *app)
{
	t_object *const	a = ft_calloc(1, sizeof(t_object));

	if (a != NULL
		&& trim_str(&line, ft_isalpha) == 2
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_vec(&line, &a->coor, MIN_COOR, MAX_COOR) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_vec(&line, &a->orientation, -1, 1) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_nbr(&line, &a->diameter, 0, MAX_COOR) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_nbr(&line, &a->height, 0, MAX_COOR) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_rgb(&line, &a->color) == 1
		&& trim_str(&line, ft_isspace) >= 0 && (*line == '#' || *line == '\0'))
	{
		a->type = CYLINDER;
		ft_lstadd_front(&app->objects, ft_lstnew(a));
		return (1);
	}
	return (0);
}
