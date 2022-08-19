/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_parse_obj.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:13:55 by weng              #+#    #+#             */
/*   Updated: 2022/06/11 22:20:46 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	test_cone(void)
{
	char	**arr;
	t_obj	*obj;

	arr = ft_split(
			"cn    1,2,3    0,0,1    0.1    0,0,255 0 ../map/water.ppm", ' ');
	obj = ft_parse_obj_cone(arr);
	if (obj == NULL)
		printf("ft_parse_obj_cone: Error!\n");
	else
		printf("ft_parse_obj_cone: OK\n");
	ft_obj_del(obj);
}

void	test_cylinder_sphere(void)
{
	char	**arr;
	t_obj	*obj;

	arr = ft_split("cy    "
			"1,2,3    0,0,1    0.1,0.1    0,0,255 0 ../map/water.ppm", ' ');
	obj = ft_parse_obj_cylinder_sphere(arr);
	if (obj == NULL)
		printf("ft_parse_obj_cylinder_sphere: Error!\n");
	else
		printf("ft_parse_obj_cylinder_sphere: OK\n");
	ft_obj_del(obj);
}

void	test_plane(void)
{
	char	**arr;
	t_obj	*obj;

	arr = ft_split(
			"pl    1,2,3    0,0,1    0,0,255 0 ../map/water.ppm", ' ');
	obj = ft_parse_obj_plane(arr);
	if (obj == NULL)
		printf("ft_parse_obj_plane: Error!\n");
	else
		printf("ft_parse_obj_plane: OK\n");
	ft_obj_del(obj);
}

void	test_obj(void)
{
	const char	*str[] = {
		"cn    1,2,3    0,0,1    0.1    0,0,255 0 ../map/water.ppm",
		"cy    1,2,3    0,0,1    0.1,0.1    0,0,255 0 ../map/water.ppm",
		"pl    1,2,3    0,0,1    0,0,255 0 ../map/water.ppm",
		"sp    1,2,3    0,0,1    0.1,0.1    0,0,255 0 ../map/water.ppm"
	};
	const int	n = sizeof(str) / sizeof(str[0]);
	int			i;
	t_list		*objs;
	t_obj		*obj;

	objs = NULL;
	i = -1;
	while (++i < n)
	{
		obj = ft_parse_obj(ft_split(str[i], ' '));
		ft_lstadd_back(&objs, ft_lstnew(obj));
	}
	printf("ft_parse_obj: OK\n");
	ft_lstclear(&objs, (void (*)(void *)) ft_obj_del);
}

int	main(void)
{
	test_cone();
	test_cylinder_sphere();
	test_plane();
	test_obj();
	return (0);
}
