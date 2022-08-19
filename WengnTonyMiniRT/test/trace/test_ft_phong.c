/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_phong.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 16:05:44 by weng              #+#    #+#             */
/*   Updated: 2022/06/11 22:27:12 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	test_hit_light(void)
{
	t_light	*light;
	t_ray	*ray;
	t_list	*objs;
	t_opt	opt;
	t_obj	*obj;

	light = ft_point_new(ft_vec4_new(5, 0, 0, 1), 0.2, ft_vec3_new(1, 1, 1));
	ray = ft_ray_new(ft_vec4_new(0, 0, 0, 1), ft_vec4_new(1, 0, 0, 0));
	objs = NULL;
	opt.colour = ft_vec3_new(1, 1, 1);
	opt.disruption = 0;
	opt.norm_map = NULL;
	obj = ft_sphere_new(ft_vec4_new(10, 0, 0, 1), ft_vec4_new(0, 1, 0, 0),
			ft_vec2_new(1, 2), &opt);
	ft_lstadd_back(&objs, ft_lstnew(obj));
	if (ft_hit_light(light, ray, objs) == 0)
		printf("ft_hit_light: Error!\n");
	else
		printf("ft_hit_light: OK\n");
	ft_light_del(light);
	ft_ray_del(ray);
	ft_lstclear(&objs, (void (*)(void *)) ft_obj_del);
}

void	test_hit_light_false(void)
{
	t_light	*light;
	t_ray	*ray;
	t_list	*objs;
	t_opt	opt;
	t_obj	*obj;

	light = ft_point_new(ft_vec4_new(5, 0, 0, 1), 0.2, ft_vec3_new(1, 1, 1));
	ray = ft_ray_new(ft_vec4_new(0, 0, 0, 1), ft_vec4_new(1, 0, 0, 0));
	objs = NULL;
	opt.colour = ft_vec3_new(1, 1, 1);
	opt.disruption = 0;
	opt.norm_map = NULL;
	obj = ft_sphere_new(ft_vec4_new(4, 0, 0, 1), ft_vec4_new(0, 1, 0, 0),
			ft_vec2_new(1, 2), &opt);
	ft_lstadd_back(&objs, ft_lstnew(obj));
	if (ft_hit_light(light, ray, objs) == 1)
		printf("ft_hit_light blocked: Error!\n");
	else
		printf("ft_hit_light blocked: OK\n");
	ft_light_del(light);
	ft_ray_del(ray);
	ft_lstclear(&objs, (void (*)(void *)) ft_obj_del);
}

void	test_light_intensity(void)
{
	t_light	*light;
	t_hit	*hit;
	t_vec	*intensity;
	t_vec	*target;
	double	factor;

	light = ft_point_new(ft_vec4_new(5, 0, 0, 1), 0.2, ft_vec3_new(1, 1, 1));
	hit = ft_hit_new(NULL, ft_vec4_new(0, 0, 0, 1), ft_vec4_new(1, 0, 0, 0));
	factor = light->param->data[0]
		+ light->param->data[1] * 5
		+ light->param->data[2] * 5 * 5;
	target = ft_vec_mul_scalar(ft_vec_copy(light->colour), 1 / factor);
	intensity = ft_light_intensity(hit, light, NULL);
	if (eq_vec(target, intensity) == 0)
		printf("ft_light_intensity: Error!\n");
	else
		printf("ft_light_intensity: OK\n");
	ft_light_del(light);
	ft_hit_del(hit);
	ft_vec_del(intensity);
	ft_vec_del(target);
}

void	test_sum_intensity(void)
{
	t_list	*light;
	t_light	*ambient;
	t_light	*l1;
	t_light	*l2;
	t_light	*l3;
	t_hit	*hit;
	t_vec	*intensity;
	t_vec	*target;
	double	factor;

	light = NULL;
	ambient = ft_ambient_new(0.2, ft_vec3_new(1, 1, 1));
	l1 = ft_point_new(ft_vec4_new(5, 0, 0, 1), 0.2, ft_vec3_new(1, 1, 1));
	l2 = ft_point_new(ft_vec4_new(10, 10, 0, 1), 0.2, ft_vec3_new(1, 1, 1));
	l3 = ft_point_new(ft_vec4_new(-10, 0, 0, 1), 0.2, ft_vec3_new(1, 1, 1));
	ft_lstadd_back(&light, ft_lstnew(l1));
	ft_lstadd_back(&light, ft_lstnew(l2));
	ft_lstadd_back(&light, ft_lstnew(l3));
	hit = ft_hit_new(NULL, ft_vec4_new(0, 0, 0, 1), ft_vec4_new(1, 0, 0, 0));
	factor = 0.2;
	factor += 1 / (l1->param->data[0]
			+ l1->param->data[1] * 5
			+ l1->param->data[2] * 5 * 5);
	factor += 1 / (l2->param->data[0]
			+ l2->param->data[1] * 10 * sqrt(2)
			+ l2->param->data[2] * 10 * 10 * 2) * cos(M_PI / 4);
	target = ft_vec_mul_scalar(ft_vec_copy(l1->colour), factor);
	intensity = ft_phong_reflection(hit, ambient, light, NULL);
	if (eq_vec(target, intensity) == 0)
		printf("ft_phong_reflection: Error!\n");
	else
		printf("ft_phong_reflection: OK\n");
	ft_light_del(ambient);
	ft_lstclear(&light, (void (*)(void *)) ft_light_del);
	ft_hit_del(hit);
	ft_vec_del(intensity);
	ft_vec_del(target);
}

void	test_clip(void)
{
	t_list	*light;
	t_light	*ambient;
	t_light	*l1;
	t_opt	opt;
	t_obj	*obj;
	t_hit	*hit;
	t_vec	*colour;
	t_vec	*intensity;
	t_vec	*target;
	double	factor;

	light = NULL;
	ambient = ft_ambient_new(0.2, ft_vec3_new(1, 1, 1));
	l1 = ft_point_new(ft_vec4_new(5, 0, 0, 1), 0.2, ft_vec3_new(1, 1, 1));
	ft_lstadd_back(&light, ft_lstnew(l1));
	opt.colour = ft_vec3_new(0.1, 0.3, 0.5);
	opt.disruption = 0;
	opt.norm_map = NULL;
	obj = ft_sphere_new(ft_vec4_new(-1, 0, 0, 1), ft_vec4_new(0, 1, 0, 0),
			ft_vec2_new(1, 2), &opt);
	hit = ft_hit_new(NULL, ft_vec4_new(0, 0, 0, 1), ft_vec4_new(1, 0, 0, 0));
	hit->obj = obj;
	factor = 0.2;
	factor += 1 / (l1->param->data[0]
			+ l1->param->data[1] * 5
			+ l1->param->data[2] * 5 * 5);
	target = ft_vec_mul_scalar(ft_vec_copy(l1->colour), factor);
	colour = obj->colour(obj, hit->point);
	target = ft_vec_mul_elem(target, colour);
	intensity = ft_limit_colour(hit, ambient, light, NULL);
	if (eq_vec(target, intensity) == 0)
		printf("ft_limit_colour: Error!\n");
	else
		printf("ft_limit_colour: OK\n");
	ft_light_del(ambient);
	ft_lstclear(&light, (void (*)(void *)) ft_light_del);
	ft_obj_del(obj);
	ft_hit_del(hit);
	ft_vec_del(colour);
	ft_vec_del(intensity);
	ft_vec_del(target);
}

int	main(void)
{
	test_hit_light();
	test_hit_light_false();
	test_light_intensity();
	test_sum_intensity();
	test_clip();
	return (0);
}
