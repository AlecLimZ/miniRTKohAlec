/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 13:10:51 by Koh               #+#    #+#             */
/*   Updated: 2022/09/15 02:52:04 by Koh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// todo 
// 1) function converts string to double
// 2) unit test

#include <fcntl.h>
#include "get_next_line.h"
#include "parser.h"

//////////////////////////////////////////////////////////////////////////////

void	error_exit(char *s)
{
	ft_putendl_fd(s, 2);
	exit(1);
}

int	if_error_exit(int ret)
{
	if (ret < 0)
	{
		perror("Error");
		exit(1);
	}
	return (ret);
}

/////////////////////////////////////////////////////////////////////////////

static int	parse_ambient(char *line, t_app *app)
{
	t_ambient *const	a = &app->ambient;

	return (
		a->loaded == 0
		&& trim_str(&line, ft_isalpha) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_nbr(&line, &a->ratio, 0, 1) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_rgb(&line, &a->color) == 1
		&& trim_str(&line, ft_isspace) >= 0
		&& (*line == '#' || *line == '\0')
		&& ++a->loaded
	);
}

static int	parse_camera(char *line, t_app *app)
{
	t_camera *const	a = &app->camera;

	return (
		a->loaded == 0
		&& trim_str(&line, ft_isalpha) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_vec(&line, &a->coor, MIN_COOR, MAX_COOR) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_vec(&line, &a->orientation, -1, 1) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_nbr(&line, &a->fov, 0, 180) == 1
		&& trim_str(&line, ft_isspace) >= 0
		&& (*line == '#' || *line == '\0')
		&& ++a->loaded
	);
}

static int	parse_light(char *line, t_app *app)
{
	t_light *const	a = &app->light;

	return (
		a->loaded == 0
		&& trim_str(&line, ft_isalpha) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_vec(&line, &a->coor, MIN_COOR, MAX_COOR) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_nbr(&line, &a->brightness, 0, 1) == 1
		&& trim_str(&line, ft_isspace) >= 1
		&& pull_rgb(&line, &a->color) == 1
		&& trim_str(&line, ft_isspace) >= 0
		&& (*line == '#' || *line == '\0')
		&& ++a->loaded
	);
}

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

void	parse_file(char *fp, t_app *app)
{
	char	*file_ext;
	int		fd;
	char	*line;

	file_ext = ft_strrchr(fp, '.');
	if (file_ext == NULL || ft_strncmp(file_ext, ".rt", 4) != 0)
		error_exit("Error: Incorrect file extension");
	fd = if_error_exit(open(fp, 0));
	while (get_next_line(fd, &line) > 0)
	{
		if (!parse_line(line, app))
		{
			ft_putendl_fd("Error: Invalid/duplicate config", 2);
			ft_putendl_fd(line, 2);
			close(fd);
		}
		free(line);
		line = NULL;
	}
	free(line);
	close(fd);
}

//////////////////////////////////////////////////////////////////////////

int	main(int argc, char **argv)
{
	t_app		app;

	app = (t_app){};
	if (argc != 2)
	{
		ft_putendl_fd("Error: Require 1 rt file", 2);
		return (1);
	}
	parse_file(argv[1], &app);
	printf("lstsize %d\n", ft_lstsize(app.objects));
	ft_lstclear(&app.objects, free);
	return (app.has_error);
}
