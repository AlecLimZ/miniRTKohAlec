/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_hit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:49:04 by weng              #+#    #+#             */
/*   Updated: 2022/06/11 22:27:12 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	test_hit_obj(void)
{
	t_opt	opt;
	t_obj	*obj1;
	t_obj	*obj2;
	t_list	*objs;
	t_hit	*hit;
	t_ray	*ray;

	objs = NULL;
	opt.colour = ft_vec3_new(1, 1, 1);
	opt.disruption = 0;
	opt.norm_map = NULL;
	obj1 = ft_sphere_new(ft_vec4_new(10, 0, 0, 1), ft_vec4_new(0, 1, 0, 0),
			ft_vec2_new(1, 2), &opt);
	opt.colour = ft_vec3_new(1, 1, 1);
	obj2 = ft_sphere_new(ft_vec4_new(5, 0, 0, 1), ft_vec4_new(0, 1, 0, 0),
			ft_vec2_new(1, 2), &opt);
	ft_lstadd_back(&objs, ft_lstnew(obj1));
	ft_lstadd_back(&objs, ft_lstnew(obj2));
	ray = ft_ray_new(ft_vec4_new(0, 0, 0, 1), ft_vec4_new(1, 0, 0, 0));
	hit = ft_hit_objs(ray, objs);
	if (hit->obj != obj2)
		printf("ft_hit_objs: Error!\n");
	else
		printf("ft_hit_objs: OK\n");
	ft_lstclear(&objs, (void (*)(void *)) ft_obj_del);
	ft_hit_del(hit);
	ft_ray_del(ray);
}

int	main(void)
{
	test_hit_obj();
	return (0);
}
