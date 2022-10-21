/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:53:36 by leng-chu          #+#    #+#             */
/*   Updated: 2022/10/21 13:40:08 by Koh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WINDOW_WIDTH 1600
# define WINDOW_HEIGHT 900
# define SMALL_WINDOW_WIDTH 800
# define SMALL_WINDOW_HEIGHT 450
# define MIN_COOR -999
# define MAX_COOR 999
# define PI 3.14159

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"
# include "ansi_colors.h"
# include "structs.h"
# include "app.h"
# include "parser.h"
//# include "vecray.h"

void		help(t_app *app);
void		benchmark(const char *s);
void		start_gui(t_app *app, int width, int height);
void		create_window(t_app *app, int width, int height);
const char	*get_object_typename(const t_object *object);
void		reload_scene(t_app *app);
float		add_or_minus(int add_condition, float step);

// gui
int			gui_keydown(unsigned int key, t_app *app);
int			gui_keyup(int keycode, t_app *app);
int			gui_mouseup(int button, int x, int y, t_app *app);
float		clamp(float value, float lo, float hi);

//util
int			ft_checklight(const t_object *object);
void		adjust_val(float *value, float step, float lo, float hi);

// rotate.c
void		rotate_x(float *y, float *z, double angle_x);
void		rotate_y(float *x, float *z, double angle_y);
void		rotate_z(float *x, float *y, double angle_z);

// control.c
void		select_next(t_app *app);

// raytrace.c
t_vec3		normalized(t_vec3 v);
void		*raytrace(const t_app *app);
t_object	*as_object(const t_list *node);

// export.c
void		export_scene(t_list *object);

#endif
