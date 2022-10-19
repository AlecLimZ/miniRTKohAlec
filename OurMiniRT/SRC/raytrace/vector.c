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

t_vec3	vadd(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){{a.x + b.x, a.y + b.y, a.z + b.z}});
}

t_vec3	vsub(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){{a.x - b.x, a.y - b.y, a.z - b.z}});
}

t_vec3	vmul(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){{a.x * b.x, a.y * b.y, a.z * b.z}});
}

// same as dot
float	mulvv(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	mulvf(t_vec3 a, float b)
{
	return ((t_vec3){{a.x * b, a.y * b, a.z * b}});
}

// t_vec3 cross(const t_vec3 v1, const t_vec3 v2) {
// 	return (t_vec3){{
	// v1.y*v2.z - v1.z*v2.y,
	// v1.z*v2.x - v1.x*v2.z,
	// v1.x*v2.y - v1.y*v2.x }};
// }
