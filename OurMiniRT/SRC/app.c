/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:00:06 by Koh               #+#    #+#             */
/*   Updated: 2022/09/16 19:28:13 by Koh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include "app.h"

#ifdef LINUX

int	mlx_destroy_display(void *mlx_ptr);

#else

int	mlx_destroy_display(void *mlx_ptr)
{
	(void)mlx_ptr;
	return (0);
}

#endif

// exit with/without error. free() before exit
void	app_exit(t_app *app, const char *error)
{
	if (app->image.ptr)
		mlx_destroy_image(app->mlx_ptr, app->image.ptr);
	if (app->win_ptr)
		mlx_destroy_window(app->mlx_ptr, app->win_ptr);
	if (app->mlx_ptr)
	{
		mlx_destroy_display(app->mlx_ptr);
		free(app->mlx_ptr);
	}
	ft_lstclear(&app->objects, free);
	if (error)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putendl_fd((char *)error, 2);
		exit(1);
	}
	exit(0);
}

// wrap system functions eg open()
int	if_errno_exit(int ret, t_app *app)
{
	if (ret == -1 && errno)
		app_exit(app, strerror(errno));
	return (ret);
}

void	*if_null_exit(void *p, t_app *app)
{
	if (p == NULL)
		app_exit(app, "Unexpected NULL pointer");
	return (p);
}

int	gui_exit(t_app *app)
{
	app_exit(app, NULL);
	return (0);
}
