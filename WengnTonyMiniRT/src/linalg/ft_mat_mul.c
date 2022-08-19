/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat_mul.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:20:19 by weng              #+#    #+#             */
/*   Updated: 2022/06/22 17:05:16 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linalg.h"

/* Returns the multiplication of scalar value and a matrix, and assign
 * the result to the matrix A, i.e. A = sA */
t_mat	*ft_mat_mul_scalar(t_mat *A, double s)
{
	size_t	i;

	i = -1;
	while (++i < A->row * A->col)
		A->data[i / A->col][i % A->col] *= s;
	return (A);
}

/* Calculates the element-wise product of a two matrices, and assign the
 * result to the matrix A, i.e. A = A ∘ B. */
t_mat	*ft_mat_mul_elem(t_mat *A, const t_mat *B)
{
	size_t	row;
	size_t	col;
	size_t	i;

	row = A->row;
	col = A->col;
	if (row != B->row || col != B->col)
		ft_perror("ft_mat_mul_elem: matrices must have the same size", EINVAL);
	i = -1;
	while (++i < row * col)
		A->data[i / col][i % col] *= B->data[i / col][i % col];
	return (A);
}

/* Returns the product of a matrix and a vector, and assign the result
 * to the vector b, i.e. b = A ⨯ b */
t_vec	*ft_mat_mul_vec(const t_mat *A, t_vec *b)
{
	t_vec	*vec;
	size_t	i;
	size_t	j;
	double	val;

	if (A->col != b->size)
		ft_perror("ft_mat_mul_vec: A->col != b->size", EINVAL);
	vec = ft_vec_new(A->row);
	i = -1;
	while (++i < A->row)
	{
		val = 0;
		j = -1;
		while (++j < A->col)
			val += A->data[i][j] * b->data[j];
		vec->data[i] = val;
	}
	ft_vec_swap(b, vec);
	ft_vec_del(vec);
	return (b);
}

/* Returns the product of two matrices, and assign the result to matrix
 * A, i.e. A = A x B */
t_mat	*ft_mat_mul(t_mat *A, const t_mat *B)
{
	t_mat	*mat;
	size_t	i;
	size_t	j;

	if (A->col != B->row)
		ft_perror("ft_mat_mul: column of matrix A != row of matrix B", EINVAL);
	mat = ft_mat_empty(A->row, B->col);
	i = -1;
	while (++i < A->row * B->col)
	{
		j = -1;
		while (++j < A->col)
			mat->data[i / mat->col][i % mat->col]
				+= A->data[i / mat->col][j] * B->data[j][i % mat->col];
	}
	ft_mat_swap(mat, A);
	ft_mat_del(mat);
	return (A);
}
