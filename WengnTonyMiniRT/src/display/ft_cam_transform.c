/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cam_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hloke <hloke@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:13:40 by hloke             #+#    #+#             */
/*   Updated: 2022/06/21 11:06:45 by hloke            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

void	ft_cam_rotate_x(t_cam *cam, double theta)
{
	t_mat	*transform;

	if (cam == NULL)
		return ;
	transform = ft_affine_rotate_x(theta);
	transform = ft_mat_mul(transform, cam->rotate);
	ft_mat_swap(transform, cam->rotate);
	ft_mat_del(transform);
	ft_mat_del(cam->to_world);
	ft_mat_del(cam->fr_world);
	cam->to_world = ft_affine_transform(cam->centre, cam->rotate);
	cam->fr_world = ft_mat_affine_inverse(ft_mat_copy(cam->to_world));
}

void	ft_cam_rotate_y(t_cam *cam, double theta)
{
	t_mat	*transform;

	if (cam == NULL)
		return ;
	transform = ft_affine_rotate_y(theta);
	transform = ft_mat_mul(transform, cam->rotate);
	ft_mat_swap(transform, cam->rotate);
	ft_mat_del(transform);
	ft_mat_del(cam->to_world);
	ft_mat_del(cam->fr_world);
	cam->to_world = ft_affine_transform(cam->centre, cam->rotate);
	cam->fr_world = ft_mat_affine_inverse(ft_mat_copy(cam->to_world));
}

void	ft_cam_rotate_z(t_cam *cam, double theta)
{
	t_mat	*transform;

	if (cam == NULL)
		return ;
	transform = ft_affine_rotate_z(theta);
	transform = ft_mat_mul(transform, cam->rotate);
	ft_mat_swap(transform, cam->rotate);
	ft_mat_del(transform);
	ft_mat_del(cam->to_world);
	ft_mat_del(cam->fr_world);
	cam->to_world = ft_affine_transform(cam->centre, cam->rotate);
	cam->fr_world = ft_mat_affine_inverse(ft_mat_copy(cam->to_world));
}

void	ft_cam_translate(t_cam *cam, double dx, double dy, double dz)
{
	t_mat	*transform;

	if (cam == NULL)
		return ;
	transform = ft_affine_translate(dx, dy, dz);
	cam->centre = ft_mat_mul_vec(transform, cam->centre);
	ft_mat_del(transform);
	ft_mat_del(cam->to_world);
	ft_mat_del(cam->fr_world);
	cam->to_world = ft_affine_transform(cam->centre, cam->rotate);
	cam->fr_world = ft_mat_affine_inverse(ft_mat_copy(cam->to_world));
}
