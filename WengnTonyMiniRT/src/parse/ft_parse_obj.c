/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 15:24:36 by weng              #+#    #+#             */
/*   Updated: 2022/06/22 17:01:57 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

/* Parse the options of an object.
 * Specification: colour disruption map
 */
static void	ft_parse_opt(char **arr, t_opt *opt)
{
	t_vec	*colour;
	t_vec	*disruption;

	if (ft_array_size(arr) > 3)
		printf("ft_parse_opt: Invalid number of parameters");
	colour = ft_parse_vector(arr[0], 3, 0, 255);
	colour = ft_vec_mul_scalar(colour, 1 / 255.999999);
	disruption = ft_parse_vector(arr[1], 1, 0, 1);
	opt->colour = colour;
	opt->disruption = (int) disruption->data[0];
	if (arr[2] != NULL)
		opt->norm_map = ft_strdup(arr[2]);
	else
		opt->norm_map = NULL;
	ft_vec_del(disruption);
}

/* Parse a line into a cone object
 * Specification:
 *     cn centre orientation height colour disruption map
 */
t_obj	*ft_parse_obj_cone(char **arr)
{
	t_vec	*ctr;
	t_vec	*orient;
	t_vec	*dim;
	t_opt	opt;
	t_obj	*obj;

	if (ft_array_size(arr) < 6)
		printf("ft_parse_obj_cone: Invalid number of parameters");
	ctr = ft_parse_vector(arr[1], 3, -INFINITY, INFINITY);
	ctr = ft_vec_append(ctr, 1);
	orient = ft_parse_vector(arr[2], 3, -1, 1);
	orient = ft_vec_append(orient, 0);
	dim = ft_parse_vector(arr[3], 1, FLT_EPSILON, INFINITY);
	ft_parse_opt(&arr[4], &opt);
	obj = ft_cone_new(ctr, orient, dim->data[0], &opt);
	ft_vec_del(dim);
	ft_array_del(arr, free);
	return (obj);
}

/* Parse a line into a cylinder or sphere object
 * Specification:
 *     cy centre orientation dimension colour disruption map
 */
t_obj	*ft_parse_obj_cylinder_sphere(char **arr)
{
	t_vec	*ctr;
	t_vec	*orient;
	t_vec	*dim;
	t_opt	opt;
	t_obj	*obj;

	if (ft_array_size(arr) < 6)
		printf("ft_parse_obj_cylinder_sphere: Invalid number of parameters");
	ctr = ft_parse_vector(arr[1], 3, -INFINITY, INFINITY);
	ctr = ft_vec_append(ctr, 1);
	orient = ft_parse_vector(arr[2], 3, -1, 1);
	orient = ft_vec_append(orient, 0);
	dim = ft_parse_vector(arr[3], 2, FLT_EPSILON, INFINITY);
	ft_parse_opt(&arr[4], &opt);
	if (ft_strcmp(arr[0], "cy") == 0)
		obj = ft_cylinder_new(ctr, orient, dim, &opt);
	else
		obj = ft_sphere_new(ctr, orient, dim, &opt);
	ft_array_del(arr, free);
	return (obj);
}

/* Parse a line into a plane object
 * Specification:
 *     pl centre orientation colour disruption map
 */
t_obj	*ft_parse_obj_plane(char **arr)
{
	t_vec	*ctr;
	t_vec	*orient;
	t_opt	opt;
	t_obj	*obj;

	if (ft_array_size(arr) < 5)
		printf("ft_parse_obj_plane: Invalid number of parameters");
	ctr = ft_parse_vector(arr[1], 3, -INFINITY, INFINITY);
	ctr = ft_vec_append(ctr, 1);
	orient = ft_parse_vector(arr[2], 3, -1, 1);
	orient = ft_vec_append(orient, 0);
	ft_parse_opt(&arr[3], &opt);
	obj = ft_plane_new(ctr, orient, &opt);
	ft_array_del(arr, free);
	return (obj);
}

/* Dispatcher function to generate the right object, or raise error if
 * the an unknown identifier is given. */
t_obj	*ft_parse_obj(char **arr)
{
	const char		*id[] = {"cn", "cy", "pl", "sp"};
	static t_obj	*(*func[])(char **arr) = {
		&ft_parse_obj_cone, &ft_parse_obj_cylinder_sphere,
		&ft_parse_obj_plane, &ft_parse_obj_cylinder_sphere};
	const int		size = sizeof(id) / sizeof(id[0]);
	int				i;

	i = -1;
	while (++i < size)
	{
		if (ft_strcmp(arr[0], id[i]) == 0)
			return (func[i](arr));
	}
	ft_perror(ft_strjoin("Unrecognised identifier ", arr[0]), EINVAL);
	return (NULL);
}
