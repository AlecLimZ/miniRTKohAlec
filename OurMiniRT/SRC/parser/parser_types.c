/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 02:18:26 by Koh               #+#    #+#             */
/*   Updated: 2022/09/15 02:29:08 by Koh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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