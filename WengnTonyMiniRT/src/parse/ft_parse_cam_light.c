/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_cam_light.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 10:11:03 by weng              #+#    #+#             */
/*   Updated: 2022/06/22 17:01:49 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

/* Parse a line into a camera object
 * Specification: C centre orientation fov
 */
t_cam	*ft_parse_camera(char **arr)
{
	static int	count = 0;
	t_vec		*ctr;
	t_vec		*orient;
	t_vec		*fov;
	t_cam		*cam;

	if (arr == NULL)
	{
		count = 0;
		return (NULL);
	}
	if (++count > 1)
		ft_perror("ft_parse_camera: More than one camera is defined", EINVAL);
	if (ft_array_size(arr) != 4)
		ft_perror("ft_parse_camera: Invalid number of parameters", EINVAL);
	ctr = ft_parse_vector(arr[1], 3, -INFINITY, INFINITY);
	ctr = ft_vec_append(ctr, 1);
	orient = ft_parse_vector(arr[2], 3, -1, 1);
	orient = ft_vec_append(orient, 0);
	fov = ft_parse_vector(arr[3], 1, 0, 180);
	cam = ft_camera_new(ctr, orient, fov->data[0]);
	ft_array_del(arr, free);
	ft_vec_del(fov);
	return (cam);
}

/* Parse a line into a ambient light object
 * Specification: A ratio colour
 */
t_light	*ft_parse_light_ambient(char **arr)
{
	static int	count = 0;
	t_vec		*ratio;
	t_vec		*colour;
	t_light		*ambient;

	if (arr == NULL)
	{
		count = 0;
		return (NULL);
	}
	if (++count > 1)
		ft_perror("ft_parse_light_ambient: More than one ambient is defined.",
			EINVAL);
	if (ft_array_size(arr) != 3)
		ft_perror("ft_parse_light_ambient: Invalid number of parameters",
			EINVAL);
	ratio = ft_parse_vector(arr[1], 1, 0, 1);
	colour = ft_parse_vector(arr[2], 3, 0, 255);
	colour = ft_vec_mul_scalar(colour, 1 / 255.999999);
	ambient = ft_ambient_new(ratio->data[0], colour);
	ft_array_del(arr, free);
	ft_vec_del(ratio);
	return (ambient);
}

/* Parse a line into a point light object
 * Specification: lp centre ratio colour
 */
t_light	*ft_parse_light_point(char **arr)
{
	t_vec		*ctr;
	t_vec		*ratio;
	t_vec		*colour;
	t_light		*point;

	if (ft_array_size(arr) != 4)
		ft_perror("ft_parse_light_point: Invalid number of parameters", EINVAL);
	ctr = ft_parse_vector(arr[1], 3, -INFINITY, INFINITY);
	ctr = ft_vec_append(ctr, 1);
	ratio = ft_parse_vector(arr[2], 1, 0, 1);
	colour = ft_parse_vector(arr[3], 3, 0, 255);
	colour = ft_vec_mul_scalar(colour, 1 / 255.999999);
	point = ft_point_new(ctr, ratio->data[0], colour);
	ft_array_del(arr, free);
	ft_vec_del(ratio);
	return (point);
}

/* Parse a line into a spot light object
 * Specification: ls centre orientation ratio colour
 */
t_light	*ft_parse_light_spot(char **arr)
{
	t_vec		*ctr;
	t_vec		*orient;
	t_vec		*ratio;
	t_vec		*colour;
	t_light		*spot;

	if (ft_array_size(arr) != 5)
		ft_perror("ft_parse_light_spot: Invalid number of parameters", EINVAL);
	ctr = ft_parse_vector(arr[1], 3, -INFINITY, INFINITY);
	ctr = ft_vec_append(ctr, 1);
	orient = ft_parse_vector(arr[2], 3, -1, 1);
	orient = ft_vec_append(orient, 0);
	ratio = ft_parse_vector(arr[3], 1, 0, 1);
	colour = ft_parse_vector(arr[4], 3, 0, 255);
	colour = ft_vec_mul_scalar(colour, 1 / 255.999999);
	spot = ft_spot_new(ctr, orient, ratio->data[0], colour);
	ft_array_del(arr, free);
	ft_vec_del(ratio);
	return (spot);
}
