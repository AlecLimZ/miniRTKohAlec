/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 13:10:51 by Koh               #+#    #+#             */
/*   Updated: 2022/09/16 18:17:41 by Koh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// todo 
// 1) function converts string to double
// 2) unit test

#include "parser.h"

// a scene must have only 1 ambient, camera, light. they are stored in struct
// "A <ratio> <r,g,b>" eg "A 0.2 255,255,25"
static bool	parse_ambient(char *line, t_app *app)
{
	t_object *const	a = ft_calloc(1, sizeof(t_object));
	double			ratio;

	ft_lstadd_front(&app->objects, ft_lstnew(a));
	if (a)
		a->type = AMBIENT;
	app->ambient = a;
	++app->ambient_count;
	if (a != NULL
		&& trim_str(&line, ft_isalpha) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_nbr(&line, &ratio, 0, 1) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_rgb(&line, &a->color) == 1
		&& trim_str(&line, ft_isspace) >= 0
		&& (*line == '#' || *line == '\0'))
	{
		a->color.r *= ratio;
		a->color.g *= ratio;
		a->color.b *= ratio;
		return (true);
	}
	return (false);
}

// "L <x,y,z> <brightness> <r,g,b>" eg "L -40.0,50.0,0.0 0.6 10,0,255"
static bool	parse_light(char *line, t_app *app)
{
	t_object *const	a = ft_calloc(1, sizeof(t_object));
	double			brightness;

	ft_lstadd_front(&app->objects, ft_lstnew(a));
	if (a)
		a->type = LIGHT;
	++app->light_count;
	if (a != NULL
		&& trim_str(&line, ft_isalpha) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_vec(&line, &a->coor, MIN_COOR, MAX_COOR) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_nbr(&line, &brightness, 0, 1) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_rgb(&line, &a->color) == 1
		&& trim_str(&line, ft_isspace) >= 0
		&& (*line == '#' || *line == '\0'))
	{
		a->color.r *= brightness;
		a->color.g *= brightness;
		a->color.b *= brightness;
		return (true);
	}
	return (false);
}

// "li <x,y,z> <brightness> <r,g,b>" eg "L -40.0,50.0,0.0 0.6 10,0,255"
static bool	parse_light_bonus(char *line, t_app *app)
{
	t_object *const	a = ft_calloc(1, sizeof(t_object));
	double			brightness;

	ft_lstadd_front(&app->objects, ft_lstnew(a));
	if (a)
		a->type = LIGHT_BONUS;
	if (a != NULL
		&& trim_str(&line, ft_isalpha) == 2
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_vec(&line, &a->coor, MIN_COOR, MAX_COOR) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_nbr(&line, &brightness, 0, 1) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_rgb(&line, &a->color) == 1
		&& trim_str(&line, ft_isspace) >= 0
		&& (*line == '#' || *line == '\0'))
	{
		a->color.r *= brightness;
		a->color.g *= brightness;
		a->color.b *= brightness;
		return (true);
	}
	return (false);
}

// parse value into struct
// return 1 if empty/remark line or valid config line
// return 0 if invalid/duplicate config
static bool	parse_line(char *line, t_app *app)
{
	const void	*f[] = {
		"A", &parse_ambient,
		"C", &parse_camera,
		"L", &parse_light,
		"sp", &parse_sphere,
		"pl", &parse_plane,
		"cy", &parse_cylinder,
		"li", &parse_light_bonus,
		"co", &parse_cone_bonus,
		NULL,
	};
	const void	**p = f;

	trim_str(&line, ft_isspace);
	if (*line == '#' || *line == '\0')
		return (1);
	while (p[0] && ft_strncmp(line, p[0], ft_strlen(p[0])) != 0)
		p += 2;
	return (p[0] && ((int (*)(char *, t_app *))p[1])(line, app));
}

// entry point to parser
// rt-file as input, app struct as output
// if any error, it will app_exit() which includes cleanup
void	parse_file(char *fp, t_app *app)
{
	const char	*file_ext = ft_strrchr(fp, '.');
	int			fd;
	char		*line;

	if (file_ext == NULL || ft_strncmp(file_ext, ".rt", 4) != 0)
		app_exit(app, "Incorrect file extension");
	fd = if_errno_exit(open(fp, 0), app);
	while (get_next_line(fd, &line) > 0)
	{
		if (!parse_line(line, app))
		{
			ft_putendl_fd(line, 2);
			app_exit(app, "Invalid/duplicate config");
		}
		free(line);
		line = NULL;
	}
	free(line);
	close(fd);
	if (app->ambient_count != 1)
		app_exit(app, "Ambient(A) must be configured and only once.");
	if (app->camera_count != 1)
		app_exit(app, "Camera(C) must be configured and only once.");
	if (app->light_count != 1)
		app_exit(app, "Light(L) must be configured and only once.");
}
