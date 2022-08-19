/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_camera.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 16:42:14 by weng              #+#    #+#             */
/*   Updated: 2022/06/20 21:21:35 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "element.h"

/* Returns a new camera.
 * 
 * The screen is assumed to be 1 unit away from camera and the image
 * resolution is 400:300.
 * 
 * @param ctr		4D vector containing the coordinates of the centre of camera
 * @param orient	4D vector containing the orientation vector. This
 * 					orientation vector is the direction the camera is
 * 					pointing towards.
 * @param fov		the field of view in degree, within range (0 - 180)
 */
t_cam	*ft_camera_new(t_vec *ctr, t_vec *orient, double fov)
{
	t_cam	*camera;

	camera = malloc(sizeof(t_cam));
	if (camera == NULL)
		return (NULL);
	camera->fov = fov;
	camera->near = 1;
	camera->reso_x = 400;
	camera->reso_y = 300;
	camera->lx = camera->near * tan(fov / 2 * M_PI / 180);
	camera->ly = camera->lx * camera->reso_y / camera->reso_x;
	camera->centre = ctr;
	orient = ft_vec_normalise(orient);
	orient = ft_vec_mul_scalar(orient, -1);
	camera->rotate = ft_affine_rotate(orient);
	ft_vec_del(orient);
	camera->to_world = ft_affine_transform(camera->centre, camera->rotate);
	camera->fr_world = ft_mat_affine_inverse(ft_mat_copy(camera->to_world));
	if (camera->to_world == NULL || camera->fr_world == NULL)
	{
		ft_camera_del(camera);
		return (NULL);
	}
	return (camera);
}

/* Return a ray in the world coordinate, given a coordinate on the
 * screen or NULL if the index is out of bound. */
t_ray	*ft_camera_ray(t_cam *camera, int i, int j)
{
	t_vec	*org;
	t_vec	*dir;
	t_ray	*ray;

	if (i < 0 || j < 0 || i >= camera->reso_x || j >= camera->reso_y)
		return (NULL);
	org = ft_vec4_new(0, 0, 0, 1);
	dir = ft_vec4_new(
			camera->lx * (2 * (double) i / (camera->reso_x - 1) - 1),
			camera->ly * (-2 * (double) j / (camera->reso_y - 1) + 1),
			-camera->near,
			0);
	ray = ft_ray_new(org, dir);
	return (ft_ray_transform(camera->to_world, ray));
}

/* Deleta a camera */
void	ft_camera_del(t_cam *camera)
{
	if (camera == NULL)
		return ;
	ft_vec_del(camera->centre);
	ft_mat_del(camera->rotate);
	ft_mat_del(camera->to_world);
	ft_mat_del(camera->fr_world);
	free(camera);
}
