/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hloke <hloke@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 13:46:48 by hloke             #+#    #+#             */
/*   Updated: 2022/06/16 15:48:58 by hloke            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

/* Allocate memory for the t_mlx struct */
t_mlx	*ft_mlx_new(int width, int height)
{
	t_mlx	*mlx;

	mlx = ft_calloc(1, sizeof(t_mlx));
	if (mlx == NULL)
		ft_perror("ft_mlx_new", ENOMEM);
	mlx->width = width;
	mlx->height = height;
	return (mlx);
}

/* Initialise a minilibx window */
void	ft_mlx_init(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(
			mlx->mlx_ptr, mlx->width, mlx->height, "MINIRT");
}

/* Deletes t_mlx struct from memory and exit program */
int	ft_mlx_del(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	ft_light_del(mlx->ambient);
	ft_lstclear(&mlx->lights, (void (*)(void *)) ft_light_del);
	ft_lstclear(&mlx->objs, (void (*)(void *)) ft_obj_del);
	ft_camera_del(mlx->cam);
	ft_mlx_image_del(mlx->image);
	free(mlx->mlx_ptr);
	free(mlx);
	printf("Minirt is exiting.\n");
	exit (EXIT_SUCCESS);
	return (0);
}
