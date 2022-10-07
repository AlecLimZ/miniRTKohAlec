/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:53:36 by leng-chu          #+#    #+#             */
/*   Updated: 2022/09/23 16:00:06 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "key_codes.h"
# include "../../mlx_linux/mlx.h"
# include "../../minilibx_macos/mlx.h"
# include "get_next_line.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include "ansi_colors.h"
# include "vecray.h"
# include "hittable.h"

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		px;
	int		len;
	int		end;
}	t_data;

void	ft_pixel(t_data *data, int x, int y, int color);
int		rgbtohex2(double a, double r, double g, double b);

#endif
