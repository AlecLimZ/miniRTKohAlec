/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3C.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <leng-chu@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 13:31:04 by leng-chu          #+#    #+#             */
/*   Updated: 2022/09/16 15:53:13 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vecray.h"

void	v_init(t_vec3 *v, const double r, const double g, const double b)
{
	v->rgb[0] = r;
	v->rgb[1] = g;
	v->rgb[2] = b;
}

t_vec3	new_dividev(t_vec3 *v, const double t)
{
	double	d;

	d = 1 / t;
	return (new_xv(d, v));
}

double	ft_dot(const t_vec3 *u, const t_vec3 *v)
{
	return (u->rgb[0] * v->rgb[0]
		+ u->rgb[1] * v->rgb[1]
		+ u->rgb[2] * v->rgb[2]);
}

t_vec3	new_cross(const t_vec3 *u, const t_vec3 *v)
{
	t_vec3	tmp;

	tmp.rgb[0] = u->rgb[1] * v->rgb[2] - u->rgb[2] * v->rgb[1];
	tmp.rgb[1] = u->rgb[2] * v->rgb[0] - u->rgb[0] * v->rgb[2];
	tmp.rgb[2] = u->rgb[0] * v->rgb[1] - u->rgb[1] * v->rgb[0];
	return (tmp);
}

// v / v.length()
t_vec3	new_unitvector(t_vec3 *v)
{
	t_vec3	tmp;
	double	len;

	len = sqrt(ft_squared_len(v));
	tmp = new_dividev(v, len);
	return (tmp);
}
