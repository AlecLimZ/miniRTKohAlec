/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:19:34 by Koh               #+#    #+#             */
/*   Updated: 2022/09/16 16:56:33 by Koh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <fcntl.h>
# include "miniRT.h"

// parser
// this is the main/entry function triggering remaining functions
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
