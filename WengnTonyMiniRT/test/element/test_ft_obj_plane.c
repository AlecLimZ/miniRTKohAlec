/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_obj_plane.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 13:45:06 by weng              #+#    #+#             */
/*   Updated: 2022/06/22 22:51:15 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "element.h"

void	test_new(void)
{
	t_obj	*plane;
	t_vec	*point;
	t_vec	*norm;
	t_opt	opt;

	point = ft_vec4_new(0, 1, 2, 1);
	norm = ft_vec4_new(3, 4, 5, 0);
	opt.colour = ft_vec3_new(0, 0, 0);
	opt.disruption = 0;
	opt.norm_map = NULL;
	plane = ft_plane_new(ft_vec_copy(point), ft_vec_copy(norm), &opt);
	norm->data[3] = -norm->data[0] * point->data[0]
		- norm->data[1] * point->data[1]
		- norm->data[2] * point->data[2];
	if (plane->dimension != NULL)
		printf("ft_plane_new: Error!\n");
	else
		printf("ft_plane_new: OK\n");
	ft_obj_del(plane);
	ft_vec_del(point);
	ft_vec_del(norm);
}

void	test_intersect(void)
{
	t_obj	*plane;
	t_ray	*ray;
	t_vec	*point;
	t_vec	norm;
	t_vec	*target_p;
	t_vec	*target_n;
	t_opt	opt;

	point = ft_vec_new(4);
	norm.data = NULL;
	target_p = ft_vec4_new(1, 1, 0, 1);
	target_n = ft_vec4_new(1, 1, 0, 0);
	opt.colour = ft_vec3_new(1, 2, 3);
	opt.disruption = 0;
	opt.norm_map = NULL;
	plane = ft_plane_new(ft_vec_copy(target_p), ft_vec_copy(target_n), &opt);
	ray = ft_ray_new(
			ft_vec4_new(0, 0, 0, 1),
			ft_vec4_new(1, 1, 0, 0));
	plane->intersect(plane, ray, point, &norm);
	target_n = ft_vec_normalise(target_n);
	if (eq_vec(point, target_p) == 0
		|| (eq_vec(&norm, target_n) == 0
			&& eq_vec(&norm, ft_vec_mul_scalar(target_n, -1)) == 0))
		printf("ft_plane_intersect: Error!\n");
	else
		printf("ft_plane_intersect: OK\n");
	ft_obj_del(plane);
	ft_ray_del(ray);
	ft_vec_del(target_p);
	ft_vec_del(target_n);
	ft_vec_del(point);
	free(norm.data);
}

void	test_no_intersect(void)
{
	t_obj	*plane;
	t_ray	*ray;
	t_vec	*point;
	t_vec	norm;
	t_vec	*target_p;
	t_vec	*target_n;
	t_opt	opt;

	target_p = ft_vec4_new(1, 1, 0, 1);
	target_n = ft_vec4_new(1, 1, 0, 0);
	point = ft_vec_new(4);
	norm.data = NULL;
	opt.colour = ft_vec3_new(1, 2, 3);
	opt.disruption = 0;
	opt.norm_map = NULL;
	plane = ft_plane_new(ft_vec_copy(target_p), ft_vec_copy(target_n), &opt);
	ray = ft_ray_new(
			ft_vec4_new(0, 0, 0, 1),
			ft_vec4_new(-1, -1, 0, 0));
	if (plane->intersect(plane, ray, point, &norm) == 1)
		printf("ft_plane_intersect no intersect: Error!\n");
	else
		printf("ft_plane_intersect no intersect: OK\n");
	ft_obj_del(plane);
	ft_ray_del(ray);
	ft_vec_del(target_p);
	ft_vec_del(target_n);
	ft_vec_del(point);
	free(norm.data);
}

void	test_normal(void)
{
	t_obj	*plane;
	t_ray	*ray;
	t_vec	*point;
	t_vec	norm;
	t_vec	*target_n;
	t_opt	opt;

	norm.data = NULL;
	target_n = ft_vec4_new(-1, -1, 0, 0);
	point = ft_vec_new(4);
	opt.colour = ft_vec3_new(1, 2, 3);
	opt.disruption = 0;
	opt.norm_map = NULL;
	plane = ft_plane_new(ft_vec4_new(1, 1, 0, 1), ft_vec_copy(target_n), &opt);
	ray = ft_ray_new(
			ft_vec4_new(0, 0, 0, 1),
			ft_vec4_new(1, 1, 0, 0));
	plane->intersect(plane, ray, point, &norm);
	target_n = ft_vec_normalise(target_n);
	if (eq_vec(&norm, target_n) == 0
		|| eq_double(ft_vec_len(&norm), 1) == 0
		|| ft_vec_angle(ray->dir, &norm) < M_PI / 2)
		printf("ft_plane_normal: Error!\n");
	else
		printf("ft_plane_normal: OK\n");
	ft_obj_del(plane);
	ft_ray_del(ray);
	ft_vec_del(target_n);
	ft_vec_del(point);
	free(norm.data);
}

int	main(void)
{
	test_new();
	test_intersect();
	test_no_intersect();
	test_normal();
	return (0);
}
