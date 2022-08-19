/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_vec_op.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 09:48:22 by weng              #+#    #+#             */
/*   Updated: 2022/05/22 16:29:20 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linalg.h"

void	test_add(void)
{
	t_vec	*a;
	t_vec	*b;
	t_vec	*target;

	a = ft_vec3_new(1, 2, 3);
	b = ft_vec3_new(4, 5, 6);
	a = ft_vec_add(a, b);
	target = ft_vec3_new(5, 7, 9);
	if (eq_vec(a, target) == 0)
		printf("ft_vec_add: Error!\n");
	else
		printf("ft_vec_add: OK\n");
	ft_vec_del(a);
	ft_vec_del(b);
	ft_vec_del(target);
}

void	test_sub(void)
{
	t_vec	*a;
	t_vec	*b;
	t_vec	*target;

	a = ft_vec3_new(1, 2, 3);
	b = ft_vec3_new(6, 5, 4);
	a = ft_vec_sub(a, b);
	target = ft_vec3_new(-5, -3, -1);
	if (eq_vec(a, target) == 0)
		printf("ft_vec_sub: Error!\n");
	else
		printf("ft_vec_sub: OK\n");
	ft_vec_del(a);
	ft_vec_del(b);
	ft_vec_del(target);
}

void	test_len(void)
{
	t_vec	*a;
	double	val;

	a = ft_vec3_new(3, 4, 12);
	val = ft_vec_len(a);
	if (eq_double(13, val) == 0)
		printf("ft_vec_len: Error!\n");
	else
		printf("ft_vec_len: OK\n");
	ft_vec_del(a);
}

void	test_angle(void)
{
	t_vec	*a;
	t_vec	*b;
	double	val;

	a = ft_vec3_new(1, 0, 0);
	b = ft_vec3_new(1, 1, 0);
	val = ft_vec_angle(a, b);
	if (eq_double(M_PI / 4, val) == 0)
		printf("ft_vec_angle: Error!\n");
	else
		printf("ft_vec_angle: OK\n");
	ft_vec_del(a);
	ft_vec_del(b);
}

void	test_normalise(void)
{
	t_vec	*a;
	double	val;

	a = ft_vec3_new(3, 4, 12);
	ft_vec_normalise(a);
	val = ft_vec_len(a);
	if (eq_double(1, val) == 0)
		printf("ft_vec_normalise: Error!\n");
	else
		printf("ft_vec_normalise: OK\n");
	ft_vec_del(a);
}

int	main(void)
{
	test_add();
	test_sub();
	test_len();
	test_angle();
	test_normalise();
	return (0);
}
