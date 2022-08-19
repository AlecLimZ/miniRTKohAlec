/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_affine.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 12:15:24 by weng              #+#    #+#             */
/*   Updated: 2022/05/12 13:58:33 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linalg.h"

/* Returns the affine transformation matrix for translation. */
t_mat	*ft_affine_translate(double dx, double dy, double dz)
{
	t_mat	*mat;

	mat = ft_mat_identity(4);
	mat->data[0][3] = dx;
	mat->data[1][3] = dy;
	mat->data[2][3] = dz;
	return (mat);
}

/*
Returns the affine transformation matrix for scaling. It's assuming
object is scaled evenly in all 3 dimensions.
*/
t_mat	*ft_affine_scale(double scale)
{
	t_mat	*mat;
	size_t	i;

	mat = ft_mat_identity(4);
	i = -1;
	while (++i < 3)
		mat->data[i][i] = scale;
	return (mat);
}

/* Returns the affine transformation matrix for rotation about x-axis. */
t_mat	*ft_affine_rotate_x(double theta)
{
	t_mat	*mat;
	double	cos_theta;
	double	sin_theta;

	cos_theta = cos(theta);
	sin_theta = sin(theta);
	mat = ft_mat_identity(4);
	mat->data[1][1] = cos_theta;
	mat->data[1][2] = -sin_theta;
	mat->data[2][1] = sin_theta;
	mat->data[2][2] = cos_theta;
	return (mat);
}

/* Returns the affine transformation matrix for rotation about y-axis. */
t_mat	*ft_affine_rotate_y(double theta)
{
	t_mat	*mat;
	double	cos_theta;
	double	sin_theta;

	cos_theta = cos(theta);
	sin_theta = sin(theta);
	mat = ft_mat_identity(4);
	mat->data[0][0] = cos_theta;
	mat->data[0][2] = sin_theta;
	mat->data[2][0] = -sin_theta;
	mat->data[2][2] = cos_theta;
	return (mat);
}

/* Returns the affine transformation matrix for rotation about z-axis. */
t_mat	*ft_affine_rotate_z(double theta)
{
	t_mat	*mat;
	double	cos_theta;
	double	sin_theta;

	cos_theta = cos(theta);
	sin_theta = sin(theta);
	mat = ft_mat_identity(4);
	mat->data[0][0] = cos_theta;
	mat->data[0][1] = -sin_theta;
	mat->data[1][0] = sin_theta;
	mat->data[1][1] = cos_theta;
	return (mat);
}
