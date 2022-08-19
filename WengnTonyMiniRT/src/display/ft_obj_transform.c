/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_obj_transform.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 13:45:02 by hloke             #+#    #+#             */
/*   Updated: 2022/06/22 23:05:48 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

void	ft_obj_rotate_x(t_obj *obj, double theta)
{
	t_mat	*transform;

	if (obj == NULL)
		return ;
	transform = ft_affine_rotate_x(theta);
	transform = ft_mat_mul(transform, obj->rotate);
	ft_mat_swap(transform, obj->rotate);
	ft_mat_del(transform);
	ft_mat_del(obj->to_world);
	ft_mat_del(obj->fr_world);
	obj->to_world = ft_affine_transform(obj->centre, obj->rotate);
	obj->fr_world = ft_mat_affine_inverse(ft_mat_copy(obj->to_world));
}

void	ft_obj_rotate_y(t_obj *obj, double theta)
{
	t_mat	*transform;

	if (obj == NULL)
		return ;
	transform = ft_affine_rotate_y(theta);
	transform = ft_mat_mul(transform, obj->rotate);
	ft_mat_swap(transform, obj->rotate);
	ft_mat_del(transform);
	ft_mat_del(obj->to_world);
	ft_mat_del(obj->fr_world);
	obj->to_world = ft_affine_transform(obj->centre, obj->rotate);
	obj->fr_world = ft_mat_affine_inverse(ft_mat_copy(obj->to_world));
}

void	ft_obj_rotate_z(t_obj *obj, double theta)
{
	t_mat	*transform;

	if (obj == NULL)
		return ;
	transform = ft_affine_rotate_z(theta);
	transform = ft_mat_mul(transform, obj->rotate);
	ft_mat_swap(transform, obj->rotate);
	ft_mat_del(transform);
	ft_mat_del(obj->to_world);
	ft_mat_del(obj->fr_world);
	obj->to_world = ft_affine_transform(obj->centre, obj->rotate);
	obj->fr_world = ft_mat_affine_inverse(ft_mat_copy(obj->to_world));
}

void	ft_obj_scale(t_obj *obj, double scale)
{
	t_mat	*transform;

	if (obj == NULL)
		return ;
	transform = ft_affine_scale(scale);
	transform = ft_mat_mul(transform, obj->to_world);
	ft_mat_swap(obj->to_world, transform);
	ft_mat_del(transform);
	ft_mat_del(obj->fr_world);
	obj->fr_world = ft_mat_affine_inverse(ft_mat_copy(obj->to_world));
}

void	ft_obj_translate(t_obj *obj, double dx, double dy, double dz)
{
	t_mat	*transform;

	if (obj == NULL)
		return ;
	transform = ft_affine_translate(dx, dy, dz);
	obj->centre = ft_mat_mul_vec(transform, obj->centre);
	ft_mat_del(transform);
	ft_mat_del(obj->to_world);
	ft_mat_del(obj->fr_world);
	obj->to_world = ft_affine_transform(obj->centre, obj->rotate);
	obj->fr_world = ft_mat_affine_inverse(ft_mat_copy(obj->to_world));
}
