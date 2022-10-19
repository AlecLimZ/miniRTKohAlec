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

static bool	are_valid_objects(t_app *app)
{
	bool	is_valid;

	is_valid = true;
	if (app->object_count[AMBIENT] != 1)
	{
		is_valid = false;
		ft_putendl_fd("Ambient(A) must be configured and only once.", 2);
	}
	if (app->object_count[CAMERA] != 1)
	{
		is_valid = false;
		ft_putendl_fd("Camera(C) must be configured and only once.", 2);
	}
	if (app->object_count[LIGHT] != 1)
	{
		is_valid = false;
		ft_putendl_fd("Light(L) must be configured and only once.", 2);
	}
	return (is_valid);
}

// parse value into struct
// return 1 if empty/remark line or valid config line
// return 0 if invalid/duplicate config
static bool	parse_line(char *line, t_app *app)
{
	t_object				object;
	t_object				*content;
	const t_object_parser 	*pfunc = (t_object_parser[]){
		parse_ambient, parse_camera, parse_light, parse_sphere, parse_plane,
		parse_cylinder, parse_light_bonus, parse_cone_bonus, NULL};

	trim_str(&line, ft_isspace);
	if (*line == '#' || *line == '\0')
		return (true);
	while (*pfunc)
	{
		object = (*pfunc)(line);
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
		++pfunc;
	}
	return (false);
}

// entry point to parser
// rt-file as input, app struct as output
// if any error, it will app_exit() which includes cleanup
void	parse_file(const char *fp, t_app *app)
{
	int			fd;
	char		*line;
	bool		has_config_error;
	const char	*file_ext = ft_strrchr(fp, '.');

	if (file_ext == NULL || ft_strncmp(file_ext, ".rt", 4) != 0)
		app_exit(app, "Incorrect file extension");
	fd = if_errno_exit(open(fp, 0), app);
	has_config_error = false;
	while (get_next_line(fd, &line) > 0)
	{
		if (!parse_line(line, app))
		{
			has_config_error = true;
			ft_putstr_fd("Invalid config: ", 2);
			ft_putendl_fd(line, 2);
		}
		free(line);
		line = NULL;
	}
	free(line);
	close(fd);
	if (!are_valid_objects(app) || has_config_error)
		app_exit(app, "Invalid rt file.");
}
