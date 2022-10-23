/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:19:34 by Koh               #+#    #+#             */
/*   Updated: 2022/10/23 14:37:53 by Koh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <fcntl.h>
# include <stdbool.h>
# include "miniRT.h"

typedef t_object	(*t_object_parser)(char *);

// parser
void				parse_file(const char *fp, t_app *app);
//				^^^ this is the entry function triggering remaining functions

// parse_lights
t_object			parse_ambient(char *line);
t_object			parse_light(char *line);
t_object			parse_light_bonus(char *line);

// parser_types
t_object			parse_sphere(char *line);
t_object			parse_plane(char *line);
t_object			parse_cylinder(char *line);
t_object			parse_cone_bonus(char *line);
t_object			parse_camera(char *line);

// parser_utils
int					trim_chr(char **line, char c);
int					trim_str(char **s, int (*f)(int));
int					pull_nbr(char **line, float *d, float min, float max);
int					pull_vec(char **line, t_vec3 *d, float min, float max);
int					pull_rgb(char **line, t_vec3 *d);

// parser_utils_2
double				ft_strtod(const char *str, char **endptr);
int					ft_isspace(int c);

#endif
