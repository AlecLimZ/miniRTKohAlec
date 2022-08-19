/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_mat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:09:06 by weng              #+#    #+#             */
/*   Updated: 2022/05/13 14:15:58 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linalg.h"

void	test_empty(void)
{
	const double	ptr[] = {0, 0, 0, 0, 0, 0};
	t_mat			*mat;
	t_mat			*target;

	mat = ft_mat_empty(2, 3);
	target = ft_mat_new(2, 3, ptr);
	if (eq_mat(mat, target) == 0)
		printf("ft_mat_empty: Error!\n");
	else
		printf("ft_mat_empty: OK\n");
	ft_mat_del(mat);
	ft_mat_del(target);
}

void	test_new(void)
{
	const double	ptr[] = {1, 2.3, 45.6, 7, 8, 9.0};
	t_mat			*mat;
	size_t			row;
	size_t			col;
	size_t			i;

	row = 3;
	col = 2;
	mat = ft_mat_new(row, col, ptr);
	if (mat->row != row || mat->col != col)
		printf("ft_mat_new: Error!\n");
	else
	{
		i = -1;
		while (++i < row * col)
		{
			if (eq_double(ptr[i], mat->data[i / col][i % col]) == 0)
				break ;
		}
		if (i == row * col)
			printf("ft_mat_new: OK\n");
		else
			printf("ft_mat_new: Error!\n");
	}
	ft_mat_del(mat);
}

void	test_copy(void)
{
	const double	ptr[3] = {1, 2.3, 45.6};
	t_mat			*mat;
	t_mat			*cpy;

	mat = ft_mat_new(3, 1, ptr);
	cpy = ft_mat_copy(mat);
	if (eq_mat(mat, cpy) == 0)
		printf("ft_mat_copy: Error!\n");
	else
		printf("ft_mat_copy: OK\n");
	ft_mat_del(mat);
	ft_mat_del(cpy);
}

void	test_identity(void)
{
	const double	ptr[] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
	t_mat			*mat;
	t_mat			*target;

	mat = ft_mat_identity(4);
	target = ft_mat_new(4, 4, ptr);
	if (eq_mat(mat, target) == 0)
		printf("ft_mat_identity: Error!\n");
	else
		printf("ft_mat_identity: OK\n");
	ft_mat_del(mat);
	ft_mat_del(target);
}

int	main(void)
{
	test_empty();
	test_new();
	test_copy();
	test_identity();
	return (0);
}
