/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:33:11 by leng-chu          #+#    #+#             */
/*   Updated: 2022/09/15 19:00:42 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "miniRT.h"

typedef struct s_data	t_data;

int		rgbtohex2(double a, double r, double g, double b);
void	ft_pixel(t_data *data, int x, int y, int color);

#endif
