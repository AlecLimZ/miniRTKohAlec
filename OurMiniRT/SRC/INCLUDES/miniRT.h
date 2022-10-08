/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:53:36 by leng-chu          #+#    #+#             */
/*   Updated: 2022/09/16 19:56:16 by Koh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

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

int		gui_input(unsigned int key, t_app *app);
int		gui_render(t_app *app);

void	rotate_x(float *y, float *z, double angle_x);
void	rotate_y(float *x, float *z, double angle_y);
void	rotate_z(float *x, float *y, double angle_z);

#endif
