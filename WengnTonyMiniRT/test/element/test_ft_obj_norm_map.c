/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_obj_norm_map.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:27:02 by weng              #+#    #+#             */
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
	opt.colour = ft_vec3_new(0.7294, 0.8235, 0.8745);
	opt.disruption = 0;
	opt.norm_map = ft_strdup("../map/water.ppm");
	cone = ft_cone_new(
			ft_vec4_new(0, 0, 0, 1), ft_vec4_new(0, 0.75, 1, 0), 2, &opt);
	ft_lstadd_back(&objs, ft_lstnew(cone));
	img = ft_render(cam, ambient, lights, objs);
	if (ft_image_2_ppm(img, "test_cone_norm_map.ppm", 6) == 0)
		printf("ft_cone_norm_map: Error!\n");
	else
		printf("ft_cone_norm_map: OK\n");
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
	opt.colour = ft_vec3_new(0.3569, 0.6353, 0.5137);
	opt.disruption = 0;
	opt.norm_map = ft_strdup("../map/earth.ppm");
	cy = ft_cylinder_new(
			ft_vec4_new(0, 0, 0, 1), ft_vec4_new(0, 0.75, 1, 0),
			ft_vec2_new(1, 2), &opt);
	ft_lstadd_back(&objs, ft_lstnew(cy));
	img = ft_render(cam, ambient, lights, objs);
	if (ft_image_2_ppm(img, "test_cylinder_norm_map.ppm", 6) == 0)
		printf("ft_cylinder_norm_map: Error!\n");
	else
		printf("ft_cylinder_norm_map: OK\n");
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
	ambient = ft_ambient_new(.3, ft_vec3_new(1, 1, 1));
	lights = NULL;
	light = ft_point_new(ft_vec4_new(3, 0, 5, 1), .8, ft_vec3_new(1, 1, 1));
	ft_lstadd_back(&lights, ft_lstnew(light));
	objs = NULL;
	opt.colour = ft_vec3_new(0.5137, 0.3216, 0.2745);
	opt.disruption = 0;
	opt.norm_map = ft_strdup("../map/brick.ppm");
	plane = ft_plane_new(ft_vec4_new(0, -10, 0, 1), ft_vec4_new(0, 1, 1, 0),
			&opt);
	ft_lstadd_back(&objs, ft_lstnew(plane));
	img = ft_render(cam, ambient, lights, objs);
	if (ft_image_2_ppm(img, "test_plane_norm_map.ppm", 6) == 0)
		printf("ft_plane_norm_map: Error!\n");
	else
		printf("ft_plane_norm_map: OK\n");
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
	ambient = ft_ambient_new(0.1, ft_vec3_new(1, 1, 1));
	lights = NULL;
	light = ft_point_new(ft_vec4_new(5, 0, 5, 1), .8, ft_vec3_new(1, 1, 1));
	ft_lstadd_back(&lights, ft_lstnew(light));
	objs = NULL;
	opt.colour = ft_vec3_new(0.9, 0.9, 0.9);
	opt.disruption = 0;
	opt.norm_map = ft_strdup("../map/golfball.ppm");
	sphere = ft_sphere_new(ft_vec4_new(0, 0, 0, 1), ft_vec4_new(0, 1, 0, 0),
			ft_vec2_new(1, 2), &opt);
	ft_lstadd_back(&objs, ft_lstnew(sphere));
	img = ft_render(cam, ambient, lights, objs);
	if (ft_image_2_ppm(img, "test_sphere_norm_map.ppm", 6) == 0)
		printf("ft_sphere_norm_map: Error!\n");
	else
		printf("ft_sphere_norm_map: OK\n");
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
