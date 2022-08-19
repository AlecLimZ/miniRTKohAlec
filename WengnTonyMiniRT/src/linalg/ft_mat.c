/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:56:24 by weng              #+#    #+#             */
/*   Updated: 2022/05/17 13:53:55 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linalg.h"

/* Returns an empty matrix of size (row, col) */
t_mat	*ft_mat_empty(size_t row, size_t col)
{
	t_mat	*retval;
	size_t	i;

	if (row == 0 || col == 0)
		return (NULL);
	retval = malloc(sizeof(t_mat));
	if (retval != NULL)
	{
		retval->row = row;
		retval->col = col;
		retval->data = ft_calloc(row, sizeof(double *));
		if (retval->data == NULL)
			return (ft_mat_del(retval));
		i = -1;
		while (++i < row)
		{
			retval->data[i] = ft_calloc(col, sizeof(double));
			if (retval->data[i] == NULL)
				return (ft_mat_del(retval));
		}
	}
	return (retval);
}

/* Returns a new row x col matrix with the element values given by 'ptr'. */
t_mat	*ft_mat_new(size_t row, size_t col, const double *ptr)
{
	t_mat	*mat;
	size_t	i;

	mat = ft_mat_empty(row, col);
	i = -1;
	while (++i < row * col)
		mat->data[i / col][i % col] = ptr[i];
	return (mat);
}

/* Returns a copy of the input matrix */
t_mat	*ft_mat_copy(const t_mat *A)
{
	t_mat	*mat;
	size_t	r;

	if (A == NULL)
		return (NULL);
	mat = ft_mat_empty(A->row, A->col);
	if (mat != NULL)
	{
		r = A->row;
		while (r-- > 0)
			ft_memmove(mat->data[r], A->data[r], A->col * sizeof(double));
	}
	return (mat);
}

/* Returns an n x n identity matrix. */
t_mat	*ft_mat_identity(size_t n)
{
	t_mat	*mat;
	size_t	i;

	mat = ft_mat_empty(n, n);
	if (mat != NULL)
	{
		i = -1;
		while (++i < n)
			mat->data[i][i] = 1;
	}
	return (mat);
}

/* Free memory associated with a matrix. */
t_mat	*ft_mat_del(t_mat *mat)
{
	if (mat == NULL)
		return (NULL);
	if (mat->data != NULL)
	{
		while (mat->row-- > 0)
			free(mat->data[mat->row]);
		free(mat->data);
	}
	free(mat);
	return (NULL);
}
