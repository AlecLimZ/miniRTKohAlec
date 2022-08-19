/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ft_parse_scene.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 16:22:21 by weng              #+#    #+#             */
/*   Updated: 2022/06/11 23:29:32 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	test_open_scene(void)
{
	int	fd;

	fd = ft_open_scene("../scenes/template.rt");
	printf("ft_open_scene: OK\n");
	close(fd);
}

void	test_split_scene(void)
{
	char	**arr;

	arr = ft_split_scene("a\t\tb\tc\t\t", '\t');
	if (ft_array_size(arr) != 5)
		printf("ft_split_scene: Error!\n");
	else
		printf("ft_split_scene: OK\n");
	ft_array_del(arr, free);
}

void	test_parse_scene(void)
{
	t_cam	*cam;
	t_light	*ambient;
	t_list	*lights;
	t_list	*objs;

	ambient = NULL;
	lights = NULL;
	objs = NULL;
	cam = ft_parse_scene("../scenes/template.rt", &ambient, &lights, &objs);
	printf("ft_parse_scene: OK\n");
	ft_camera_del(cam);
	ft_light_del(ambient);
	ft_lstclear(&lights, (void (*)(void *)) ft_light_del);
	ft_lstclear(&objs, (void (*)(void *)) ft_obj_del);
}

int	main(void)
{
	test_open_scene();
	test_split_scene();
	test_parse_scene();
	return (0);
}
