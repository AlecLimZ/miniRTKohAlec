/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
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
static t_object	parse_ambient(char *line)
{
	t_object	a;

	a.type = OBJECT_TYPE_ERROR;
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
static t_object	parse_light(char *line)
{
	t_object	a;

	a.type = OBJECT_TYPE_ERROR;
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
static t_object	parse_light_bonus(char *line)
{
	t_object	a;

	a.type = OBJECT_TYPE_ERROR;
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

// parse value into struct
// return 1 if empty/remark line or valid config line
// return 0 if invalid/duplicate config
	// (t_object (*[])(char *)){
	// t_object (*const *f)(char *) 
static bool	parse_line(char *line, t_app *app)
{
	t_object		object;
	t_object		*content;
	const void		**p = (const void *[]){
		parse_ambient, parse_camera, parse_light, parse_sphere, parse_plane,
		parse_cylinder, parse_light_bonus, parse_cone_bonus, NULL};

	trim_str(&line, ft_isspace);
	if (*line == '#' || *line == '\0')
		return (1);
	while (*p)
	{
		object = ((t_object (*)(char *))*p)(line);
		if (object.type < END_OF_OBJECT_TYPE)
		{
			content = if_null_exit(ft_calloc(1, sizeof(t_object)), app);
			*content = object;
			app->object[object.type] = content;
			app->object_count[object.type] += 1;
			ft_lstadd_front(&app->objects,
				if_null_exit(ft_lstnew(content), app));
			return (true);
		}
		++p;
	}
	return (false);
}

// entry point to parser
// rt-file as input, app struct as output
// if any error, it will app_exit() which includes cleanup
void	parse_file(const char *fp, t_app *app)
{
	const int	fd = if_errno_exit(open(fp, 0), app);
	const char	*file_ext = ft_strrchr(fp, '.');
	char		*line;
	t_object	rt_object;

	if (file_ext == NULL || ft_strncmp(file_ext, ".rt", 4) != 0)
		app_exit(app, "Incorrect file extension");
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
	if (app->object_count[AMBIENT] != 1)
		app_exit(app, "Ambient(A) must be configured and only once.");
	if (app->object_count[CAMERA] != 1)
		app_exit(app, "Camera(C) must be configured and only once.");
	if (app->object_count[LIGHT] != 1)
		app_exit(app, "Light(L) must be configured and only once.");
}
