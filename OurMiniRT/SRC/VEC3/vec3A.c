/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3A.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:24:00 by leng-chu          #+#    #+#             */
/*   Updated: 2022/09/16 14:43:49 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vecray.h"

// just use sqrt()
//double	ft_length(const t_vec3 *v)
//{
//	return (sqrt(ft_squared_len(v)));
//}

double	ft_squared_len(const t_vec3 *v)
{
	return (v->rgb[0] * v->rgb[0]
		+ v->rgb[1] * v->rgb[1]
		+ v->rgb[2] * v->rgb[2]);
}

void	ft_cvntminus(t_vec3 *v)
{
	v->rgb[0] *= -1;
	v->rgb[1] *= -1;
	v->rgb[2] *= -1;
}

void	ft_plus2vecs(t_vec3 *a, const t_vec3 *b)
{
	a->rgb[0] += b->rgb[0];
	a->rgb[1] += b->rgb[1];
	a->rgb[2] += b->rgb[2];
}

void	ft_multivec(t_vec3 *v, const double b)
{
	v->rgb[0] *= b;
	v->rgb[1] *= b;
	v->rgb[2] *= b;
}

void	ft_dividevec(t_vec3 *v, const double b)
{
	v->rgb[0] /= b;
	v->rgb[1] /= b;
	v->rgb[2] /= b;
}
