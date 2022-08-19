/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light_transform.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 17:10:36 by weng              #+#    #+#             */
/*   Updated: 2022/06/23 22:36:13 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

void	ft_light_rotate_x(t_light *light, double theta)
{
	t_mat	*transform;

	if (light == NULL || light->dir == NULL)
		return ;
	transform = ft_affine_rotate_x(-theta);
	light->dir = ft_mat_mul_vec(transform, light->dir);
	ft_mat_del(transform);
}

void	ft_light_rotate_y(t_light *light, double theta)
{
	t_mat	*transform;

	if (light == NULL || light->dir == NULL)
		return ;
	transform = ft_affine_rotate_y(-theta);
	light->dir = ft_mat_mul_vec(transform, light->dir);
	ft_mat_del(transform);
}

void	ft_light_rotate_z(t_light *light, double theta)
{
	t_mat	*transform;

	if (light == NULL || light->dir == NULL)
		return ;
	transform = ft_affine_rotate_z(-theta);
	light->dir = ft_mat_mul_vec(transform, light->dir);
	ft_mat_del(transform);
}

void	ft_light_translate(t_light *light, double dx, double dy, double dz)
{
	t_mat	*transform;

	if (light == NULL)
		return ;
	transform = ft_affine_translate(dx, dy, dz);
	light->centre = ft_mat_mul_vec(transform, light->centre);
	ft_mat_del(transform);
}
