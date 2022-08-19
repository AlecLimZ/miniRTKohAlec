/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_camera.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 22:39:14 by weng              #+#    #+#             */
/*   Updated: 2022/06/10 11:52:51 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "element.h"

void	test_new_x(void)
{
	t_cam	*cam;
	t_ray	*ray1;
	t_ray	*ray2;
	t_ray	*ray3;
	t_ray	*ray4;
	t_vec	*target;

	cam = ft_camera_new(ft_vec4_new(0, 0, 0, 1), ft_vec4_new(-1, 0, 0, 0), 60);
	ray1 = ft_camera_ray(cam, cam->reso_x / 2 - 1, cam->reso_y / 2 - 1);
	ray2 = ft_camera_ray(cam, cam->reso_x / 2 - 1, cam->reso_y / 2);
	ray3 = ft_camera_ray(cam, cam->reso_x / 2, cam->reso_y / 2 - 1);
	ray4 = ft_camera_ray(cam, cam->reso_x / 2, cam->reso_y / 2);
	ray1->dir = ft_vec_add(ray1->dir, ray2->dir);
	ray1->dir = ft_vec_add(ray1->dir, ray3->dir);
	ray1->dir = ft_vec_add(ray1->dir, ray4->dir);
	ray1->dir = ft_vec_mul_scalar(ray1->dir, 1.0 / 4);
	ray1->dir = ft_vec_normalise(ray1->dir);
	target = ft_vec4_new(-1, 0, 0, 0);
	if (eq_vec(ray1->dir, target) == 0)
		printf("ft_camera_new x: Error!\n");
	else
		printf("ft_camera_new x: OK\n");
	ft_camera_del(cam);
	ft_ray_del(ray1);
	ft_ray_del(ray2);
	ft_ray_del(ray3);
	ft_ray_del(ray4);
	ft_vec_del(target);
}

void	test_new_y(void)
{
	t_cam	*cam;
	t_ray	*ray1;
	t_ray	*ray2;
	t_ray	*ray3;
	t_ray	*ray4;
	t_vec	*target;

	cam = ft_camera_new(ft_vec4_new(0, 0, 0, 1), ft_vec4_new(0, -1, 0, 0), 60);
	ray1 = ft_camera_ray(cam, cam->reso_x / 2 - 1, cam->reso_y / 2 - 1);
	ray2 = ft_camera_ray(cam, cam->reso_x / 2 - 1, cam->reso_y / 2);
	ray3 = ft_camera_ray(cam, cam->reso_x / 2, cam->reso_y / 2 - 1);
	ray4 = ft_camera_ray(cam, cam->reso_x / 2, cam->reso_y / 2);
	ray1->dir = ft_vec_add(ray1->dir, ray2->dir);
	ray1->dir = ft_vec_add(ray1->dir, ray3->dir);
	ray1->dir = ft_vec_add(ray1->dir, ray4->dir);
	ray1->dir = ft_vec_mul_scalar(ray1->dir, 1.0 / 4);
	ray1->dir = ft_vec_normalise(ray1->dir);
	target = ft_vec4_new(0, -1, 0, 0);
	if (eq_vec(ray1->dir, target) == 0)
		printf("ft_camera_new y: Error!\n");
	else
		printf("ft_camera_new y: OK\n");
	ft_camera_del(cam);
	ft_ray_del(ray1);
	ft_ray_del(ray2);
	ft_ray_del(ray3);
	ft_ray_del(ray4);
	ft_vec_del(target);
}

void	test_new_z(void)
{
	t_cam	*cam;
	t_ray	*ray1;
	t_ray	*ray2;
	t_ray	*ray3;
	t_ray	*ray4;
	t_vec	*target;

	cam = ft_camera_new(ft_vec4_new(0, 0, 0, 1), ft_vec4_new(0, 0, -1, 0), 60);
	ray1 = ft_camera_ray(cam, cam->reso_x / 2 - 1, cam->reso_y / 2 - 1);
	ray2 = ft_camera_ray(cam, cam->reso_x / 2 - 1, cam->reso_y / 2);
	ray3 = ft_camera_ray(cam, cam->reso_x / 2, cam->reso_y / 2 - 1);
	ray4 = ft_camera_ray(cam, cam->reso_x / 2, cam->reso_y / 2);
	ray1->dir = ft_vec_add(ray1->dir, ray2->dir);
	ray1->dir = ft_vec_add(ray1->dir, ray3->dir);
	ray1->dir = ft_vec_add(ray1->dir, ray4->dir);
	ray1->dir = ft_vec_mul_scalar(ray1->dir, 1.0 / 4);
	target = ft_vec4_new(0, 0, -1, 0);
	ray1->dir = ft_vec_normalise(ray1->dir);
	if (eq_vec(ray1->dir, target) == 0)
		printf("ft_camera_new z: Error!\n");
	else
		printf("ft_camera_new z: OK\n");
	ft_camera_del(cam);
	ft_ray_del(ray1);
	ft_ray_del(ray2);
	ft_ray_del(ray3);
	ft_ray_del(ray4);
	ft_vec_del(target);
}

void	test_angle_horizontal(void)
{
	t_cam	*cam;
	t_ray	*ray1;
	t_ray	*ray2;
	t_ray	*ray3;
	t_ray	*ray4;
	double	angle;

	cam = ft_camera_new(ft_vec4_new(0, 0, 0, 1), ft_vec4_new(0, 0, -1, 0), 60);
	ray1 = ft_camera_ray(cam, 0, cam->reso_y / 2 - 1);
	ray2 = ft_camera_ray(cam, 0, cam->reso_y / 2);
	ray3 = ft_camera_ray(cam, cam->reso_x - 1, cam->reso_y / 2 - 1);
	ray4 = ft_camera_ray(cam, cam->reso_x - 1, cam->reso_y / 2);
	ray1->dir = ft_vec_mul_scalar(ft_vec_add(ray1->dir, ray2->dir), 0.5);
	ray3->dir = ft_vec_mul_scalar(ft_vec_add(ray3->dir, ray4->dir), 0.5);
	angle = ft_vec_angle(ray1->dir, ray3->dir) * 180 / M_PI;
	if (eq_double(angle, 60) == 0)
		printf("ft_camera_ray horizontal: Error!\n");
	else
		printf("ft_camera_ray horizontal: OK\n");
	ft_camera_del(cam);
	ft_ray_del(ray1);
	ft_ray_del(ray2);
	ft_ray_del(ray3);
	ft_ray_del(ray4);
}

void	test_angle_vertical(void)
{
	t_cam	*cam;
	t_ray	*ray1;
	t_ray	*ray2;
	t_ray	*ray3;
	t_ray	*ray4;
	double	angle;
	double	target;

	cam = ft_camera_new(ft_vec4_new(0, 0, 0, 1), ft_vec4_new(0, 0, -1, 0), 60);
	ray1 = ft_camera_ray(cam, cam->reso_x / 2 - 1, 0);
	ray2 = ft_camera_ray(cam, cam->reso_x / 2, 0);
	ray3 = ft_camera_ray(cam, cam->reso_x / 2 - 1, cam->reso_y - 1);
	ray4 = ft_camera_ray(cam, cam->reso_x / 2, cam->reso_y - 1);
	ray1->dir = ft_vec_mul_scalar(ft_vec_add(ray1->dir, ray2->dir), 0.5);
	ray3->dir = ft_vec_mul_scalar(ft_vec_add(ray3->dir, ray4->dir), 0.5);
	angle = ft_vec_angle(ray1->dir, ray3->dir) * 180 / M_PI;
	target = 2 * atan(tan(60.0 / 2 * M_PI / 180) * 3 / 4) * 180 / M_PI;
	if (eq_double(angle, target) == 0)
		printf("ft_camera_ray vertical: Error!\n");
	else
		printf("ft_camera_ray vertical: OK\n");
	ft_camera_del(cam);
	ft_ray_del(ray1);
	ft_ray_del(ray2);
	ft_ray_del(ray3);
	ft_ray_del(ray4);
}

int	main(void)
{
	test_new_x();
	test_new_y();
	test_new_z();
	test_angle_horizontal();
	test_angle_vertical();
	return (0);
}
