/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 13:10:51 by Koh               #+#    #+#             */
/*   Updated: 2022/09/15 14:05:35 by Koh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// todo 
// 1) function converts string to double
// 2) unit test

#include "parser.h"

// a scene must have only 1 ambient, camera, light. they are stored in struct

// "A <ratio> <r,g,b>" eg "A 0.2 255,255,25"
static int	parse_ambient(char *line, t_app *app)
{
	t_ambient *const	a = &app->ambient;

	return (
		a->is_configured == 0
		&& trim_str(&line, ft_isalpha) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_nbr(&line, &a->ratio, 0, 1) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_rgb(&line, &a->color) == 1
		&& trim_str(&line, ft_isspace) >= 0
		&& (*line == '#' || *line == '\0')
		&& ++a->is_configured
	);
}

// "C <x,y,z> <orientation:x,y,z> <FOV>" eg "C -50.0,0,20 0,0,1 70"
static int	parse_camera(char *line, t_app *app)
{
	t_camera *const	a = &app->camera;

	return (
		a->is_configured == 0
		&& trim_str(&line, ft_isalpha) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_vec(&line, &a->coor, MIN_COOR, MAX_COOR) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_vec(&line, &a->orientation, -1, 1) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_nbr(&line, &a->fov, 0, 180) == 1
		&& trim_str(&line, ft_isspace) >= 0
		&& (*line == '#' || *line == '\0')
		&& ++a->is_configured
	);
}

// "L <x,y,z> <brightness> <r,g,b>" eg "L -40.0,50.0,0.0 0.6 10,0,255"
static int	parse_light(char *line, t_app *app)
{
	t_light *const	a = &app->light;

	return (
		a->is_configured == 0
		&& trim_str(&line, ft_isalpha) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_vec(&line, &a->coor, MIN_COOR, MAX_COOR) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_nbr(&line, &a->brightness, 0, 1) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_rgb(&line, &a->color) == 1
		&& trim_str(&line, ft_isspace) >= 0
		&& (*line == '#' || *line == '\0')
		&& ++a->is_configured
	);
}

// parse value into struct
// return 1 if empty/remark line or valid config line
// return 0 if invalid/duplicate config
static int	parse_line(char *line, t_app *app)
{
	const void	*f[] = {
		"A", &parse_ambient,
		"C", &parse_camera,
		"L", &parse_light,
		"sp", &parse_sphere,
		"pl", &parse_plane,
		"cy", &parse_cylinder,
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
// caller responsible for free-ing scene objects linked-list
void	parse_file(char *fp, t_app *app)
{
	char	*file_ext;
	int		fd;
	char	*line;

	file_ext = ft_strrchr(fp, '.');
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
	if (!app->ambient.is_configured || !app->camera.is_configured
		|| !app->light.is_configured)
		app_exit(app, "Ambient/Camera/Light is not configured");
}
