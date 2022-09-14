/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:19:34 by Koh               #+#    #+#             */
/*   Updated: 2022/09/15 02:37:24 by Koh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft/libft.h"

# define MIN_COOR -999
# define MAX_COOR 999

enum e_object_type
{
	CYLINDER,
	SPHERE,
	PLANE,	
};

typedef union s_vec3
{
	double	elements[3];
	struct
	{
		double	x;
		double	y;
		double	z;
	};
	struct
	{
		double	r;
		double	g;
		double	b;
	};
}	t_vec3;

typedef t_vec3	t_rgb;
typedef t_vec3	t_xyz;

typedef struct s_ambient
{
	double	ratio;
	t_rgb	color;
	int		loaded;
}	t_ambient;

typedef struct s_camera
{
	double	fov;
	t_xyz	coor;
	t_xyz	orientation;
	int		loaded;
}	t_camera;

typedef struct s_light
{
	double	brightness;
	t_xyz	coor;
	t_rgb	color;
	int		loaded;
}	t_light;

typedef struct s_object
{
	double	diameter;
	double	height;
	t_xyz	coor;
	t_rgb	color;
	t_xyz	orientation;
	char	type;
}	t_object;

typedef struct s_app
{
	int			has_error;
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_list		*objects;
}	t_app;

// parser
void	parse_file(char *fp, t_app *app);

// parser_types
int		parse_sphere(char *line, t_app *app);
int		parse_plane(char *line, t_app *app);
int		parse_cylinder(char *line, t_app *app);

// parser_utils
int		trim_str(char **s, int (*f)(int));
int		pull_nbr(char **line, double *d, double min, double max);
int		pull_vec(char **line, t_vec3 *d, double min, double max);
int		pull_rgb(char **line, t_vec3 *d);

// parser_utils_2
double	parse_double(const char *a);
int		ft_isspace(int c);

#endif
