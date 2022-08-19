/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_affine_transform.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:34:44 by weng              #+#    #+#             */
/*   Updated: 2022/05/20 10:55:16 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "element.h"

/* object z-axis is aligned to world x-axis */
void	test_rotate_x(void)
{
	t_vec	*orient;
	t_mat	*mat;
	t_mat	*target;

	orient = ft_vec4_new(1, 0, 0, 0);
	mat = ft_affine_rotate(orient);
	target = ft_affine_rotate_y(M_PI / 2);
	if (eq_mat(mat, target) == 0)
		printf("ft_affine_rotate x: Error!\n");
	else
		printf("ft_affine_rotate x: OK\n");
	ft_vec_del(orient);
	ft_mat_del(mat);
	ft_mat_del(target);
}

/* object z-axis is aligned to world x-axis */
void	test_rotate_y(void)
{
	t_vec	*orient;
	t_mat	*mat;
	t_mat	*target;

	orient = ft_vec4_new(0, 1, 0, 0);
	mat = ft_affine_rotate(orient);
	target = ft_affine_rotate_x(-M_PI / 2);
	if (eq_mat(mat, target) == 0)
		printf("ft_affine_rotate y: Error!\n");
	else
		printf("ft_affine_rotate y: OK\n");
	ft_vec_del(orient);
	ft_mat_del(mat);
	ft_mat_del(target);
}

/* object z-axis is aligned to world z-axis */
void	test_rotate_z(void)
{
	t_vec	*orient;
	t_mat	*mat;
	t_mat	*target;

	orient = ft_vec4_new(0, 0, 1, 0);
	mat = ft_affine_rotate(orient);
	target = ft_mat_identity(4);
	if (eq_mat(mat, target) == 0)
		printf("ft_affine_rotate z: Error!\n");
	else
		printf("ft_affine_rotate z OK\n");
	ft_vec_del(orient);
	ft_mat_del(mat);
	ft_mat_del(target);
}

/* object z-axis is aligned to world z-axis */
void	test_rotate_neg_z(void)
{
	t_vec	*orient;
	t_mat	*mat;
	t_mat	*target;

	orient = ft_vec4_new(0, 0, -1, 0);
	mat = ft_affine_rotate(orient);
	target = ft_affine_rotate_x(M_PI);
	if (eq_mat(mat, target) == 0)
		printf("ft_affine_rotate -z: Error!\n");
	else
		printf("ft_affine_rotate -z: OK\n");
	ft_vec_del(orient);
	ft_mat_del(mat);
	ft_mat_del(target);
}

int	main(void)
{
	test_rotate_x();
	test_rotate_y();
	test_rotate_z();
	test_rotate_neg_z();
	return (0);
}
