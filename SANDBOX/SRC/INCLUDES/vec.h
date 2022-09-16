/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:29:08 by leng-chu          #+#    #+#             */
/*   Updated: 2022/09/16 13:00:31 by leng-chu         ###   ########.fr       */
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
void	ft_cvntminus(t_vec3 *v);
void	ft_plus2vecs(t_vec3 *a, const t_vec3 *b);
void	ft_multivec(t_vec3 *v, const double b);
void	ft_dividevec(t_vec3 *v, const double b);

#endif
