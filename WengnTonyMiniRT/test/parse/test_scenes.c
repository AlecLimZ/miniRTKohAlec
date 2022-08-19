/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_scenes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weng <weng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 11:13:45 by weng              #+#    #+#             */
/*   Updated: 2022/06/13 00:58:54 by weng             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	generate_scene(char *scene)
{
	t_cam	*cam;
	t_light	*ambient;
	t_list	*lights;
	t_list	*objs;
	t_img	*img;
	char	*in_path;
	char	*out_path;

	out_path = ft_strjoin(scene, ".ppm");
	scene = ft_strjoin("../scenes/", scene);
	in_path = ft_strjoin(scene, ".rt");
	ambient = NULL;
	lights = NULL;
	objs = NULL;
	cam = ft_parse_scene(in_path, &ambient, &lights, &objs);
	img = ft_render(cam, ambient, lights, objs);
	printf("Generating %s: ", scene);
	if (ft_image_2_ppm(img, out_path, 6) == 0)
		printf("Error!\n");
	else
		printf("OK\n");
	ft_camera_del(cam);
	ft_light_del(ambient);
	ft_lstclear(&lights, (void (*)(void *)) ft_light_del);
	ft_lstclear(&objs, (void (*)(void *)) ft_obj_del);
	ft_image_del(img);
	free(scene);
	free(in_path);
	free(out_path);
	ft_parse_camera(NULL);
	ft_parse_light_ambient(NULL);
}

int	main(void)
{
	static char	*scenes[] = {
		"sphere",
		"sphere_inside",
		"cylinder",
		"cone",
		"multi-spot",
		"golfball",
	};
	const int	n = sizeof(scenes) / sizeof(scenes[0]);
	int			i;

	i = -1;
	while (++i < n)
		generate_scene(scenes[i]);
	return (0);
}
