/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Koh <Koh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 20:19:34 by Koh               #+#    #+#             */
/*   Updated: 2022/10/21 15:13:52 by Koh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// reserve d(radius x2) D(R,G,B) f(float) F(3 floats)
static void	pfmt(const char *fmt, const void **param)
{
	int	move_param;

	while (*fmt)
	{
		move_param = 0;
		if (*fmt == 'f')
			move_param = printf("%.2f", *(float *)*param);
		else if (*fmt == 'F')
			move_param = printf("%.2f,%.2f,%.2f", ((t_vec3 *)*param)->x,
					((t_vec3 *)*param)->y, ((t_vec3 *)*param)->z);
		else if (*fmt == 'd')
			move_param = printf("%.2f", (*(float *)*param) * 2);
		else if (*fmt == 'D')
			move_param = printf("%d,%d,%d",
					(int)(((t_vec3 *)*param)->x * 255.999),
					(int)(((t_vec3 *)*param)->y * 255.999),
					(int)(((t_vec3 *)*param)->z * 255.999));
		else
			printf("%c", *fmt);
		++fmt;
		if (move_param)
			++param;
	}
	printf("\n");
}

void	print_object(const t_object *o)
{
	if (o->hide)
		printf("# ");
	if (o->type == AMBIENT)
		pfmt("A	f	D	",
			(const void *[]){&o->ambient_ratio, &o->color});
	else if (o->type == LIGHT)
		pfmt("L	F		f	D	",
			(const void *[]){&o->coor, &o->light_brightness, &o->color});
	else if (o->type == LIGHT_BONUS)
		pfmt("li	F		f	D	",
			(const void *[]){&o->coor, &o->light_brightness, &o->color});
	else if (o->type == CAMERA)
		pfmt("C	F		F	f	",
			(const void *[]){&o->coor, &o->orientation, &o->camera_fov});
	else if (o->type == PLANE)
		pfmt("pl	F		F	D	",
			(const void *[]){&o->coor, &o->orientation, &o->color});
	else if (o->type == SPHERE)
		pfmt("sp	F		d	D	",
			(const void *[]){&o->coor, &o->radius, &o->color});
	else if (o->type == CYLINDER)
		pfmt("cy	F		F	d	f	D	",
			(const void *[]){&o->coor, &o->orientation,
			&o->radius, &o->height, &o->color});
	else
		printf("# unknown type %d\n", o->type);
}

static void	export_reverse_order(t_list *object)
{
	if (object->next)
		export_reverse_order(object->next);
	print_object(object->content);
}

void	export_scene(t_list *object)
{
	printf("### EXPORT BEGIN ###\n");
	export_reverse_order(object);
	printf("### EXPORT END ###\n");
}
