/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_obj_cylinder.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 22:40:32 by weng              #+#    #+#             */
/*   Updated: 2022/06/10 13:50:49 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "element.h"

void	test_new(void)
{
	t_opt	opt;
	t_obj	*cylinder;
	t_mat	*identity;

	opt.colour = ft_vec3_new(0, 0, 0);
	opt.disruption = 0;
	opt.norm_map = NULL;
	cylinder = ft_cylinder_new(
			ft_vec4_new(1, 2, 3, 1),
			ft_vec4_new(4, 5, 6, 0),
			ft_vec2_new(5, 10),
			&opt);
	identity = ft_mat_identity(4);
	ft_mat_mul(cylinder->fr_world, cylinder->to_world);
	if (eq_mat(identity, cylinder->fr_world) == 0)
		printf("ft_cylinder_new: Error!\n");
	else
		printf("ft_cylinder_new: OK\n");
	ft_obj_del(cylinder);
	ft_mat_del(identity);
}

void	test_intersect(void)
{
	t_opt	opt;
	t_obj	*cylinder;
	t_ray	*ray;
	t_vec	*point;
	t_vec	norm;
	t_vec	*target_p;
	t_vec	*target_n;

	point = ft_vec_new(4);
	norm.data = NULL;
	opt.colour = ft_vec3_new(0, 0, 0);
	opt.disruption = 0;
	opt.norm_map = NULL;
	cylinder = ft_cylinder_new(ft_vec4_new(8, 0, 0, 1),
			ft_vec4_new(0, 0, 1, 0),
			ft_vec2_new(2, 100),
			&opt);
	ray = ft_ray_new(ft_vec4_new(4, 4, 0, 1),
			ft_vec4_new(1, -1, 0, 0));
	cylinder->intersect(cylinder, ray, point, &norm);
	target_p = ft_vec4_new(8 - pow(2, 0.5), pow(2, 0.5), 0.0, 1.0);
	target_n = ft_vec4_new(-pow(2, 0.5) / 2, pow(2, 0.5) / 2, 0.0, 0.0);
	if (eq_vec(point, target_p) == 0 || eq_vec(&norm, target_n) == 0)
		printf("ft_cylinder_intersect: Error!\n");
	else
		printf("ft_cylinder_intersect: OK\n");
	ft_obj_del(cylinder);
	ft_ray_del(ray);
	ft_vec_del(target_p);
	ft_vec_del(target_n);
	ft_vec_del(point);
	free(norm.data);
}

void	test_no_intersect(void)
{
	t_opt	opt;
	t_obj	*cylinder;
	t_ray	*ray;
	t_vec	*point;
	t_vec	norm;

	point = ft_vec_new(4);
	norm.data = NULL;
	opt.colour = ft_vec3_new(0, 0, 0);
	opt.disruption = 0;
	opt.norm_map = NULL;
	cylinder = ft_cylinder_new(ft_vec4_new(4, 0, 0, 1),
			ft_vec4_new(0, 0, 1, 0),
			ft_vec2_new(1, 100),
			&opt);
	ray = ft_ray_new(ft_vec4_new(2, 2, 0, 1),
			ft_vec4_new(-1, 1, 0, 0));
	if (cylinder->intersect(cylinder, ray, point, &norm) == 1)
		printf("ft_cylinder_intersect no intersect: Error!\n");
	else
		printf("ft_cylinder_intersect no intersect: OK\n");
	ft_obj_del(cylinder);
	ft_ray_del(ray);
	ft_vec_del(point);
	free(norm.data);
}

void	test_normal(void)
{
	t_opt	opt;
	t_obj	*cylinder;
	t_ray	*ray;
	t_vec	*target;
	t_vec	point;
	t_vec	norm;

	point.data = NULL;
	norm.data = NULL;
	opt.colour = ft_vec3_new(0, 0, 0);
	opt.disruption = 0;
	opt.norm_map = NULL;
	cylinder = ft_cylinder_new(
			ft_vec4_new(0, 0, 0, 1),
			ft_vec4_new(0, 0, 1, 0),
			ft_vec2_new(2, 100),
			&opt);
	ray = ft_ray_new(ft_vec4_new(-2, 2, 0, 1), ft_vec4_new(1, -1, 0, 0));
	cylinder->intersect(cylinder, ray, &point, &norm);
	target = ft_vec4_new(-pow(2, 0.5) / 2, pow(2, 0.5) / 2, 0.0, 0.0);
	cylinder->normal(cylinder, ray, &point, &norm);
	if (eq_vec(&norm, target) == 0
		|| eq_double(ft_vec_len(&norm), 1) == 0
		|| ft_vec_angle(ray->dir, &norm) < M_PI / 2)
		printf("ft_cylinder_normal: Error!\n");
	else
		printf("ft_cylinder_normal: OK\n");
	ft_obj_del(cylinder);
	ft_ray_del(ray);
	ft_vec_del(target);
	free(point.data);
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
