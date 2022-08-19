/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 23:49:02 by weng              #+#    #+#             */
/*   Updated: 2022/06/22 16:59:27 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linalg.h"

/* Return the result of matrix A + B and assign the result to matrix A,
 * i.e. A = A + B */
t_mat	*ft_mat_add(t_mat *A, const t_mat *B)
{
	size_t	i;

	if (A->row != B->row || A->col != B->col)
		ft_perror("ft_mat_add: size of matrix A != size of matrix B", EINVAL);
	i = -1;
	while (++i < A->row * A->col)
		A->data[i / A->col][i % A->col] += B->data[i / A->col][i % A->col];
	return (A);
}

/* Return the result of matrix A - B and assign the result to matrix A,
 * i.e. A = A - B */
t_mat	*ft_mat_sub(t_mat *A, const t_mat *B)
{
	size_t	i;

	if (A->row != B->row || A->col != B->col)
		ft_perror("ft_mat_add: size of matrix A != size of matrix B", EINVAL);
	i = -1;
	while (++i < A->row * A->col)
		A->data[i / A->col][i % A->col] -= B->data[i / A->col][i % A->col];
	return (A);
}

/* Transpose of matrix A in-place. */
t_mat	*ft_mat_transpose(t_mat *A)
{
	t_mat	*mat;
	size_t	i;
	size_t	row;
	size_t	col;

	mat = ft_mat_empty(A->col, A->row);
	i = -1;
	while (++i < A->row * A->col)
	{
		row = i / A->col;
		col = i % A->col;
		mat->data[col][row] = A->data[row][col];
	}
	ft_mat_swap(mat, A);
	ft_mat_del(mat);
	return (A);
}

/* Transform an affine transformation matrix to its inverse
 *
 * Since rotation matrices are orthogonal, A is in the form
 * A = [ M  b ]
 *     [ 0  1 ]
 * where M is an orthogonal matrix, and M^-1 = M^T.
 * 
 * inv(A) = [ inv(M)  -inv(M) * b ]
 *          [   0          1      ]
 */
t_mat	*ft_mat_affine_inverse(t_mat *A)
{
	t_mat	*inv_a;
	t_vec	*b;
	size_t	i;

	if (A == NULL || A->row != A->col)
		return (NULL);
	inv_a = ft_mat_copy(A);
	inv_a = ft_mat_transpose(inv_a);
	b = ft_vec4_new(-A->data[0][3], -A->data[1][3], -A->data[2][3], 0.0);
	b = ft_mat_mul_vec(inv_a, b);
	i = -1;
	while (++i < 3)
	{
		inv_a->data[3][i] = 0;
		inv_a->data[i][3] = b->data[i];
	}
	ft_mat_swap(inv_a, A);
	ft_mat_del(inv_a);
	ft_vec_del(b);
	return (A);
}

void	ft_mat_swap(t_mat *A, t_mat *B)
{
	t_mat	temp;

	ft_memmove(&temp, A, sizeof(t_mat));
	ft_memmove(A, B, sizeof(t_mat));
	ft_memmove(B, &temp, sizeof(t_mat));
}
