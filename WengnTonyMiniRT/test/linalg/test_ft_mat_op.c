/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_mat_op.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 10:59:52 by weng              #+#    #+#             */
/*   Updated: 2022/05/20 15:40:48 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linalg.h"

void	test_add(void)
{
	const double	ptr[] = {1, 2, 3, 4};
	const double	ptr2[] = {2, 4, 6, 8};
	t_mat			*mat;
	t_mat			*target;

	mat = ft_mat_new(2, 2, ptr);
	mat = ft_mat_add(mat, mat);
	target = ft_mat_new(2, 2, ptr2);
	if (eq_mat(mat, target) == 0)
		printf("ft_mat_add: Error!\n");
	else
		printf("ft_mat_add: OK\n");
	ft_mat_del(mat);
	ft_mat_del(target);
}

void	test_sub(void)
{
	const double	ptr[] = {1, 2, 3, 4};
	t_mat			*mat;
	t_mat			*target;

	mat = ft_mat_new(2, 2, ptr);
	mat = ft_mat_sub(mat, mat);
	target = ft_mat_empty(2, 2);
	if (eq_mat(mat, target) == 0)
		printf("ft_mat_sub: Error!\n");
	else
		printf("ft_mat_sub: OK\n");
	ft_mat_del(mat);
	ft_mat_del(target);
}

void	test_transpose(void)
{
	const double	ptr[] = {1, 2, 3, 4, 5, 6};
	const double	ptr2[] = {1, 4, 2, 5, 3, 6};
	t_mat			*mat;
	t_mat			*target;

	mat = ft_mat_new(2, 3, ptr);
	mat = ft_mat_transpose(mat);
	target = ft_mat_new(3, 2, ptr2);
	if (eq_mat(mat, target) == 0)
		printf("ft_mat_transpose: Error!\n");
	else
		printf("ft_mat_transpose: OK\n");
	ft_mat_del(mat);
	ft_mat_del(target);
}

void	test_affine_inverse(void)
{
	t_mat	*x;
	t_mat	*y;
	t_mat	*t;
	t_mat	*inv;
	t_mat	*target;

	x = ft_affine_rotate_x(0.1);
	y = ft_affine_rotate_y(0.2);
	t = ft_affine_translate(1, 2, 3);
	x = ft_mat_mul(x, y);
	x = ft_mat_mul(x, t);
	inv = ft_mat_affine_inverse(ft_mat_copy(x));
	x = ft_mat_mul(x, inv);
	target = ft_mat_identity(4);
	if (eq_mat(x, target) == 0)
		printf("ft_mat_affine_inverse: Error!\n");
	else
		printf("ft_mat_affine_inverse: OK\n");
	ft_mat_del(x);
	ft_mat_del(y);
	ft_mat_del(t);
	ft_mat_del(inv);
	ft_mat_del(target);
}

void	test_swap(void)
{
	t_mat	*a;
	t_mat	*a_copy;
	t_mat	*b;
	t_mat	*b_copy;

	a = ft_mat_identity(4);
	a_copy = ft_mat_copy(a);
	b = ft_mat_identity(4);
	b = ft_mat_mul_scalar(b, -1);
	b_copy = ft_mat_copy(b);
	ft_mat_swap(a, b);
	if (eq_mat(a, b_copy) == 0 || eq_mat(b, a_copy) == 0)
		printf("ft_mat_swap: Error!\n");
	else
		printf("ft_mat_swap: OK\n");
	ft_mat_del(a);
	ft_mat_del(a_copy);
	ft_mat_del(b);
	ft_mat_del(b_copy);
}

int	main(void)
{
	test_add();
	test_sub();
	test_transpose();
	test_affine_inverse();
	test_swap();
	return (0);
}
