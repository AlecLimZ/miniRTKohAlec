/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:29:08 by leng-chu          #+#    #+#             */
/*   Updated: 2022/09/15 18:43:59 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

# include <math.h>

typedef struct s_vec3
{
	double	rgb[3];
}	t_vec3;

double	ft_squared_len(const t_vec3 *v);
double	ft_length(const t_vec3 *v);

#endif
