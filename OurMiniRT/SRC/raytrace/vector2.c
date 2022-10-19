/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 23:12:51 by Koh               #+#    #+#             */
/*   Updated: 2022/10/11 23:16:33 by Koh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

t_vec3	negate(t_vec3 v)
{
	return ((t_vec3){{-v.x, -v.y, -v.z}});
}

float	norm(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec3	normalized(t_vec3 v)
{
	return (mulvf(v, 1.f / norm(v)));
}

float	vlenf(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}
