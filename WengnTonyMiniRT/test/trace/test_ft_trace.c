/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_trace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hloke <hloke@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 22:36:05 by weng              #+#    #+#             */
/*   Updated: 2022/06/14 17:56:05 by hloke            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	test_trace_ambient(void)
{
	t_light	*ambient;
	t_ray	*ray;
	t_vec	*output;
	t_vec	*target;

	ambient = ft_ambient_new(0.1, ft_vec3_new(1, 1, 1));
	ray = ft_ray_new(ft_vec4_new(0, 0, 0, 1), ft_vec4_new(1, 0, 0, 0));
	target = ft_vec3_new(0.1, 0.1, 0.1);
	output = ft_trace(ray, ambient, NULL, NULL);
	if (eq_vec(target, output) == 0)
		printf("ft_trace ambient: Error!\n");
	else
		printf("ft_trace ambient: OK\n");
	ft_light_del(ambient);
	ft_ray_del(ray);
	ft_vec_del(output);
	ft_vec_del(target);
}

void	test_trace_diffuse(void)
{
	t_light	*ambient;
	t_ray	*ray;
	t_obj	*sphere;
	t_opt	opt;
	t_list	*objs;
	t_vec	*output;
	t_vec	*target;

	ambient = ft_ambient_new(0.1, ft_vec3_new(1, 1, 1));
	ray = ft_ray_new(ft_vec4_new(-10, 0, 0, 1), ft_vec4_new(1, 0, 0, 0));
	opt.colour = ft_vec3_new(0.1, 0.3, 0.5);
	opt.disruption = 0;
	opt.norm_map = NULL;
	sphere = ft_sphere_new(ft_vec4_new(0, 0, 0, 1), ft_vec4_new(0, 1, 0, 0),
			ft_vec2_new(1, 2), &opt);
	objs = NULL;
	ft_lstadd_back(&objs, ft_lstnew(sphere));
	target = ft_vec3_new(0.01, 0.03, 0.05);
	output = ft_trace(ray, ambient, NULL, objs);
	if (eq_vec(target, output) == 0)
		printf("ft_trace diffuse: Error!\n");
	else
		printf("ft_trace diffuse: OK\n");
	ft_light_del(ambient);
	ft_ray_del(ray);
	ft_lstclear(&objs, (void (*)(void *)) ft_obj_del);
	ft_vec_del(output);
	ft_vec_del(target);
}

void	test_render(void)
{
	t_cam	*cam;
	t_light	*ambient;
	t_light	*light;
	t_list	*lights;
	t_obj	*sphere;
	t_opt	opt;
	t_list	*objs;
	t_img	*img;

	cam = ft_camera_new(
			ft_vec4_new(0, 0, 5, 1), ft_vec4_new(0, 0, -1, 0), 70);
	ambient = ft_ambient_new(.1, ft_vec3_new(1, 1, 1));
	lights = NULL;
	light = ft_point_new(ft_vec4_new(5, 0, 5, 1), .8, ft_vec3_new(1, 1, 1));
	ft_lstadd_back(&lights, ft_lstnew(light));
	objs = NULL;
	opt.colour = ft_vec3_new(1, 0, 0);
	opt.disruption = 1;
	opt.norm_map = NULL;
	sphere = ft_sphere_new(ft_vec4_new(0, 0, 0.1, 1), ft_vec4_new(0, 1, 0, 0),
			ft_vec2_new(1, 2), &opt);
	ft_lstadd_back(&objs, ft_lstnew(sphere));
	img = ft_render(cam, ambient, lights, objs);
	if (ft_image_2_ppm(img, "test_render.ppm", 6) == 0)
		printf("ft_render: Error!\n");
	else
		printf("ft_render: OK\n");
	ft_camera_del(cam);
	ft_light_del(ambient);
	ft_lstclear(&lights, (void (*)(void *)) ft_light_del);
	ft_lstclear(&objs, (void (*)(void *)) ft_obj_del);
	ft_image_del(img);
}

int	main(void)
{
	test_trace_ambient();
	test_trace_diffuse();
	test_render();
	return (0);
}
