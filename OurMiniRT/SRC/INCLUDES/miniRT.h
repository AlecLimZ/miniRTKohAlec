/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:53:36 by leng-chu          #+#    #+#             */
/*   Updated: 2022/10/18 14:52:16 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WIN_TITLE "miniRT" \
		"  [TAB]=NextObject  [Arrows]/[I]n/[O]ut=Movement" \
		"  [1/2/3/4]=-Param1/+Param1/-Param2/+Param2" \
		"  [G]ammaCorrection  [W]indowSize  [R]eload  [E]xport"

// https://harm-smits.github.io/42docs/libs/minilibx/events.html#x11-interface
# define KEY_PRESS_EVENT 2
# define DESTROY_NOTIFY_EVENT 17
# define KEY_PRESS_MASK (1L << 0)
# define STRUCTURE_NOTIFY_MASK (1L << 17)

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"
# include "ansi_colors.h"
# include "key_codes.h"
# include "structs.h"
# include "app.h"
# include "parser.h"
# include "vecray.h"

int	    	gui_input(unsigned int key, t_app *app);
int		    gui_render(t_app *app);
void	    start_gui(t_app *app, int width, int height);

// rotate.c
void    	rotate_x(float *y, float *z, double angle_x);
void    	rotate_y(float *x, float *z, double angle_y);
void    	rotate_z(float *x, float *y, double angle_z);

// control.c
void    	select_next(t_app *app);

// raytrace.c
t_vec3	    normalized(t_vec3 v);
void	    *raytrace(const t_app *app);
t_object    *as_object(const t_list *node);

// export.c
void	export_scene(t_list *object);

#endif
