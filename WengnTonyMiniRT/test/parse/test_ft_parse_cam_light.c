/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_parse_cam_light.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 14:20:34 by weng              #+#    #+#             */
/*   Updated: 2022/06/12 00:19:42 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	test_camera(void)
{
	char	**arr;
	t_cam	*cam;

	arr = ft_split("C    0,0,0    0,0,-1    60", ' ');
	cam = ft_parse_camera(arr);
	if (cam == NULL)
		printf("ft_parse_camera: Error!\n");
	else
		printf("ft_parse_camera: OK\n");
	ft_camera_del(cam);
}

void	test_ambient(void)
{
	char	**arr;
	t_light	*ambient;

	arr = ft_split("A    0    0,0,255", ' ');
	ambient = ft_parse_light_ambient(arr);
	if (ambient == NULL)
		printf("ft_parse_light_ambient: Error!\n");
	else
		printf("ft_parse_light_ambient: OK\n");
	ft_light_del(ambient);
}

void	test_point(void)
{
	char	**arr;
	t_light	*point;

	arr = ft_split("lp    1,2,3    0    0,0,255", ' ');
	point = ft_parse_light_point(arr);
	if (point == NULL)
		printf("ft_parse_light_point: Error!\n");
	else
		printf("ft_parse_light_point: OK\n");
	ft_light_del(point);
}

void	test_spot(void)
{
	char	**arr;
	t_light	*spot;

	arr = ft_split("lp    1,2,3    0,0,1    0    0,0,255", ' ');
	spot = ft_parse_light_spot(arr);
	if (spot == NULL)
		printf("ft_parse_light_spot: Error!\n");
	else
		printf("ft_parse_light_spot: OK\n");
	ft_light_del(spot);
}

int	main(void)
{
	test_camera();
	test_ambient();
	test_point();
	test_spot();
	return (0);
}
