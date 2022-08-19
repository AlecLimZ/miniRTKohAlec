/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 23:43:27 by weng              #+#    #+#             */
/*   Updated: 2022/05/20 11:21:31 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "element.h"

/* Create a new ray with a given 'origin' and 'direction'. The direction
 * vector is normalised. */
t_ray	*ft_ray_new(t_vec *origin, t_vec *direction)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	if (ray != NULL)
	{
		ray->org = origin;
		ray->dir = ft_vec_normalise(direction);
	}
	return (ray);
}

/* Delete a given ray. */
void	ft_ray_del(t_ray *ray)
{
	if (ray == NULL)
		return ;
	ft_vec_del(ray->org);
	ft_vec_del(ray->dir);
	free(ray);
}

/* Returns a copy of a ray from memory. */
t_ray	*ft_ray_copy(t_ray *ray)
{
	t_ray	*copy;

	copy = ft_ray_new(ft_vec_copy(ray->org), ft_vec_copy(ray->dir));
	return (copy);
}

/* Transform a ray in place, given a transformation matrix */
t_ray	*ft_ray_transform(t_mat *A, t_ray *ray)
{
	ray->org = ft_mat_mul_vec(A, ray->org);
	ray->dir = ft_mat_mul_vec(A, ray->dir);
	return (ray);
}

/* Calculates the coordinate of point along a ray, and assign the result
 * to the vector pointed by 'point'. */
t_vec	*ft_ray_calc_point(t_ray *ray, double t, t_vec *point)
{
	t_vec	*vec;

	vec = ft_vec_copy(ray->dir);
	vec = ft_vec_mul_scalar(vec, t);
	vec = ft_vec_add(vec, ray->org);
	ft_vec_swap(point, vec);
	ft_vec_del(vec);
	return (point);
}
