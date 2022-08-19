/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_obj_checkerboard.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 11:00:58 by weng              #+#    #+#             */
/*   Updated: 2022/06/11 22:20:46 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	test_cone(void)
{
	t_cam	*cam;
	t_light	*ambient;
	t_light	*light;
	t_list	*lights;
	t_obj	*cone;
	t_list	*objs;
	t_opt	opt;
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
	cone = ft_cone_new(
			ft_vec4_new(0, 0, 0, 1), ft_vec4_new(0, 0.75, 1, 0), 2, &opt);
	ft_lstadd_back(&objs, ft_lstnew(cone));
	img = ft_render(cam, ambient, lights, objs);
	if (ft_image_2_ppm(img, "test_cone_checkerboard.ppm", 6) == 0)
		printf("ft_cone_checkerboard: Error!\n");
	else
		printf("ft_cone_checkerboard: OK\n");
	ft_camera_del(cam);
	ft_light_del(ambient);
	ft_lstclear(&lights, (void (*)(void *)) ft_light_del);
	ft_lstclear(&objs, (void (*)(void *)) ft_obj_del);
	ft_image_del(img);
}

void	test_cylinder(void)
{
	t_cam	*cam;
	t_light	*ambient;
	t_light	*light;
	t_list	*lights;
	t_obj	*cy;
	t_list	*objs;
	t_opt	opt;
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
	cy = ft_cylinder_new(
			ft_vec4_new(0, 0, 0, 1), ft_vec4_new(0, 0.75, 1, 0),
			ft_vec2_new(1, 2), &opt);
	ft_lstadd_back(&objs, ft_lstnew(cy));
	img = ft_render(cam, ambient, lights, objs);
	if (ft_image_2_ppm(img, "test_cylinder_checkerboard.ppm", 6) == 0)
		printf("ft_cylinder_checkerboard: Error!\n");
	else
		printf("ft_cylinder_checkerboard: OK\n");
	ft_camera_del(cam);
	ft_light_del(ambient);
	ft_lstclear(&lights, (void (*)(void *)) ft_light_del);
	ft_lstclear(&objs, (void (*)(void *)) ft_obj_del);
	ft_image_del(img);
}

void	test_plane(void)
{
	t_cam	*cam;
	t_light	*ambient;
	t_light	*light;
	t_list	*lights;
	t_obj	*plane;
	t_list	*objs;
	t_img	*img;
	t_opt	opt;

	cam = ft_camera_new(
			ft_vec4_new(0, 0, 5, 1), ft_vec4_new(0, 0, -1, 0), 70);
	ambient = ft_ambient_new(.1, ft_vec3_new(1, 1, 1));
	lights = NULL;
	light = ft_point_new(ft_vec4_new(3, 0, 5, 1), .8, ft_vec3_new(1, 1, 1));
	ft_lstadd_back(&lights, ft_lstnew(light));
	objs = NULL;
	opt.norm_map = NULL;
	opt.colour = ft_vec3_new(1, 0, 0);
	opt.disruption = 1;
	plane = ft_plane_new(ft_vec4_new(0, 0, 0, 1), ft_vec4_new(0, 1, 1, 0),
			&opt);
	ft_lstadd_back(&objs, ft_lstnew(plane));
	img = ft_render(cam, ambient, lights, objs);
	if (ft_image_2_ppm(img, "test_plane_checkerboard.ppm", 6) == 0)
		printf("ft_plane_checkerboard: Error!\n");
	else
		printf("ft_plane_checkerboard: OK\n");
	ft_camera_del(cam);
	ft_light_del(ambient);
	ft_lstclear(&lights, (void (*)(void *)) ft_light_del);
	ft_lstclear(&objs, (void (*)(void *)) ft_obj_del);
	ft_image_del(img);
}

void	test_sphere(void)
{
	t_cam	*cam;
	t_light	*ambient;
	t_light	*light;
	t_list	*lights;
	t_obj	*sphere;
	t_list	*objs;
	t_opt	opt;
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
	sphere = ft_sphere_new(ft_vec4_new(0, 0, 0, 1), ft_vec4_new(0, 1, 1, 0),
			ft_vec2_new(1, 1), &opt);
	ft_lstadd_back(&objs, ft_lstnew(sphere));
	img = ft_render(cam, ambient, lights, objs);
	if (ft_image_2_ppm(img, "test_sphere_checkerboard.ppm", 6) == 0)
		printf("ft_sphere_checkerboard: Error!\n");
	else
		printf("ft_sphere_checkerboard: OK\n");
	ft_camera_del(cam);
	ft_light_del(ambient);
	ft_lstclear(&lights, (void (*)(void *)) ft_light_del);
	ft_lstclear(&objs, (void (*)(void *)) ft_obj_del);
	ft_image_del(img);
}

int	main(void)
{
	test_cone();
	test_cylinder();
	test_plane();
	test_sphere();
	return (0);
}
