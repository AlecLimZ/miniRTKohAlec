/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 15:22:22 by weng              #+#    #+#             */
/*   Updated: 2022/05/20 10:55:16 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "element.h"

void	test_new(void)
{
	t_ray	*ray;
	t_vec	*origin;
	t_vec	*direction;

	origin = ft_vec4_new(1, 2, 3, 1);
	direction = ft_vec4_new(4, 5, 6, 0);
	ray = ft_ray_new(ft_vec_copy(origin), ft_vec_copy(direction));
	direction = ft_vec_normalise(direction);
	if (eq_vec(origin, ray->org) == 0
		|| eq_vec(direction, ray->dir) == 0)
		printf("ft_ray_new: Error!\n");
	else
		printf("ft_ray_new: OK\n");
	ft_ray_del(ray);
	ft_vec_del(origin);
	ft_vec_del(direction);
}

void	test_copy(void)
{
	t_ray	*ray;
	t_ray	*copy;

	ray = ft_ray_new(
			ft_vec4_new(1, 2, 3, 1),
			ft_vec4_new(4, 5, 6, 0));
	copy = ft_ray_copy(ray);
	if (eq_vec(ray->org, copy->org) == 0
		|| eq_vec(ray->dir, copy->dir) == 0)
		printf("ft_ray_copy: Error!\n");
	else
		printf("ft_ray_copy: OK\n");
	ft_ray_del(ray);
	ft_ray_del(copy);
}

void	test_transform(void)
{
	t_mat	*transform;
	t_mat	*translate;
	t_ray	*ray;
	t_ray	*copy;

	transform = ft_affine_rotate_x(1.0);
	translate = ft_affine_translate(1.0, 2.0, 3.0);
	transform = ft_mat_mul(transform, translate);
	ray = ft_ray_new(
			ft_vec4_new(1, 2, 3, 1),
			ft_vec4_new(4, 5, 6, 0));
	copy = ft_ray_copy(ray);
	copy = ft_ray_transform(transform, copy);
	transform = ft_mat_affine_inverse(transform);
	copy = ft_ray_transform(transform, copy);
	if (eq_vec(ray->org, copy->org) == 0
		|| eq_vec(ray->dir, copy->dir) == 0)
		printf("ft_ray_transform: Error!\n");
	else
		printf("ft_ray_transfrom: OK\n");
	ft_mat_del(transform);
	ft_mat_del(translate);
	ft_ray_del(ray);
	ft_ray_del(copy);
}

void	test_calc_point(void)
{
	t_ray	*ray;
	t_vec	point;
	t_vec	*target;
	double	t;

	t = 12;
	ray = ft_ray_new(
			ft_vec4_new(0, 1, 2, 1),
			ft_vec4_new(3, 4, 5, 0));
	target = ft_vec_mul_scalar(ft_vec_copy(ray->dir), t);
	target = ft_vec_add(target, ray->org);
	ft_ray_calc_point(ray, t, &point);
	if (eq_vec(&point, target) == 0)
		printf("ft_ray_calc_point: Error!\n");
	else
		printf("ft_ray_calc_point: OK\n");
	ft_ray_del(ray);
	free(point.data);
	ft_vec_del(target);
}

int	main(void)
{
	test_new();
	test_copy();
	test_transform();
	test_calc_point();
	return (0);
}
