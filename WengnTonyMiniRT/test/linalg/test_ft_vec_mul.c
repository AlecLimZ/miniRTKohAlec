/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_vec_mul.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:17:46 by weng              #+#    #+#             */
/*   Updated: 2022/05/13 14:15:58 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linalg.h"

void	test_scalar(void)
{
	t_vec	*vec;
	t_vec	*target;

	vec = ft_vec3_new(1, 2, 3);
	target = ft_vec3_new(4, 8, 12);
	vec = ft_vec_mul_scalar(vec, 4);
	if (eq_vec(vec, target) == 0)
		printf("ft_vec_mul_scalar: Error!\n");
	else
		printf("ft_vec_mul_scalar: OK\n");
	ft_vec_del(vec);
	ft_vec_del(target);
}

void	test_elem(void)
{
	t_vec	*a;
	t_vec	*b;
	t_vec	*target;

	a = ft_vec3_new(1, 2, 3);
	b = ft_vec3_new(4, 5, 6);
	a = ft_vec_mul_elem(a, b);
	target = ft_vec3_new(4, 10, 18);
	if (eq_vec(a, target) == 0)
		printf("ft_vec_mul_elem: Error!\n");
	else
		printf("ft_vec_mul_elem: OK\n");
	ft_vec_del(a);
	ft_vec_del(b);
	ft_vec_del(target);
}

void	test_dot(void)
{
	t_vec	*a;
	t_vec	*b;
	double	val;

	a = ft_vec3_new(1, 2, 3);
	b = ft_vec3_new(4, 5, 6);
	val = ft_vec_mul_dot(a, b);
	if (eq_double(32, val) == 0)
		printf("ft_vec_mul_dot: Error!\n");
	else
		printf("ft_vec_mul_dot: OK\n");
	ft_vec_del(a);
	ft_vec_del(b);
}

void	test_cross(void)
{
	t_vec	*a;
	t_vec	*b;
	t_vec	*target;

	a = ft_vec3_new(1, 2, 3);
	b = ft_vec3_new(4, 5, 6);
	a = ft_vec_mul_cross(a, b);
	target = ft_vec3_new(-3, 6, -3);
	if (eq_vec(a, target) == 0)
		printf("ft_vec_mul_cross: Error!\n");
	else
		printf("ft_vec_mul_cross: OK\n");
	ft_vec_del(a);
	ft_vec_del(b);
	ft_vec_del(target);
}

void	test_triple(void)
{
	t_vec	*a;
	t_vec	*b;
	t_vec	*c;
	double	val;

	a = ft_vec3_new(1, 2, 3);
	b = ft_vec3_new(4, 5, 6);
	c = ft_vec3_new(7, 8, 9);
	val = ft_vec_mul_triple(a, b, c);
	if (eq_double(0, val) == 0)
		printf("ft_vec_mul_triple: Error!\n");
	else
		printf("ft_vec_mul_triple: OK\n");
	ft_vec_del(a);
	ft_vec_del(b);
	ft_vec_del(c);
}

int	main(void)
{
	test_scalar();
	test_elem();
	test_dot();
	test_cross();
	test_triple();
	return (0);
}
