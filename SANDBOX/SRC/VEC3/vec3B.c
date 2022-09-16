/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3B.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <leng-chu@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 13:11:00 by leng-chu          #+#    #+#             */
/*   Updated: 2022/09/16 16:24:42 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vecray.h"

t_vec3	new_plus2v(const t_vec3 *u, const t_vec3 *v)
{
	t_vec3	tmp;

	tmp.rgb[0] = u->rgb[0] + v->rgb[0];
	tmp.rgb[1] = u->rgb[1] + v->rgb[1];
	tmp.rgb[2] = u->rgb[2] + v->rgb[2];
	return (tmp);
}

t_vec3	new_minus2v(const t_vec3 *u, const t_vec3 *v)
{
	t_vec3	tmp;

	tmp.rgb[0] = u->rgb[0] - v->rgb[0];
	tmp.rgb[1] = u->rgb[1] - v->rgb[1];
	tmp.rgb[2] = u->rgb[2] - v->rgb[2];
	return (tmp);
}

t_vec3	new_x2v(const t_vec3 *u, const t_vec3 *v)
{
	t_vec3	tmp;

	tmp.rgb[0] = u->rgb[0] * v->rgb[0];
	tmp.rgb[1] = u->rgb[1] * v->rgb[1];
	tmp.rgb[2] = u->rgb[2] * v->rgb[2];
	return (tmp);
}

t_vec3	new_xv(const double t, const t_vec3 *v)
{
	t_vec3	tmp;

	tmp.rgb[0] = t * v->rgb[0];
	tmp.rgb[1] = t * v->rgb[1];
	tmp.rgb[2] = t * v->rgb[2];
	return (tmp);
}
