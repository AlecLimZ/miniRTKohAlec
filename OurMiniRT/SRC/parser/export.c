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

// reserve d (radius x2) D(R,G,B) f(float) F(3 floats)
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

static void	print_object(const t_object *o)
{
	if (o->type == AMBIENT)
		pfmt("A	f	D	# ratio color",
			(const void *[]){&o->ambient_ratio, &o->color});
	else if (o->type == LIGHT)
		pfmt("L	F		f	D	# center brightness color",
			(const void *[]){&o->coor, &o->light_brightness, &o->color});
	else if (o->type == LIGHT_BONUS)
		pfmt("li	F		f	D	# center brightness color",
			(const void *[]){&o->coor, &o->light_brightness, &o->color});
	else if (o->type == CAMERA)
		pfmt("C	F		F	f	# center orientation fov",
			(const void *[]){&o->coor, &o->orientation, &o->camera_fov});
	else if (o->type == PLANE)
		pfmt("pl	F		F	D	# center orientation color",
			(const void *[]){&o->coor, &o->orientation, &o->color});
	else if (o->type == SPHERE)
		pfmt("sp	F		f	D	# center diameter color",
			(const void *[]){&o->coor, &o->radius, &o->color});
	else if (o->type == CYLINDER)
		pfmt(
			"cy	F		F	f	f	D	# center orient diameter height color",
			(const void *[]){&o->coor, &o->orientation,
			&o->radius, &o->height, &o->color});
	else
		printf("# unknonw %d\n", o->type);
}

void	export_scene(t_list *object)
{
	if (object->next)
		export_scene(object->next);
	print_object(object->content);
}

// void	export_scene3(t_list *object)
// {
// 	if (object->next)
// 		export_scene(object->next);
// 	if (as_object(object)->type == AMBIENT)
// 		printf("A	%.2f	%d,%d,%d"
// 			"	# ratio color\n",
// 			as_object(object)->ambient_ratio,
// 			(int)(as_object(object)->color.x * 255.999),
// 			(int)(as_object(object)->color.y * 255.999),
// 			(int)(as_object(object)->color.z * 255.999));
// 	else if (as_object(object)->type == LIGHT)
// 		printf("L	%.2f,%.2f,%.2f		%.2f	%d,%d,%d"
// 			"	# center brightness color\n",
// 			as_object(object)->coor.x,
// 			as_object(object)->coor.y,
// 			as_object(object)->coor.z,
// 			as_object(object)->light_brightness,
// 			(int)(as_object(object)->color.x * 255.999),
// 			(int)(as_object(object)->color.y * 255.999),
// 			(int)(as_object(object)->color.z * 255.999));
// 	else if (as_object(object)->type == LIGHT_BONUS)
// 		printf("li	%.2f,%.2f,%.2f		%.2f	%d,%d,%d"
// 			"	# center brightness color\n",
// 			as_object(object)->coor.x,
// 			as_object(object)->coor.y,
// 			as_object(object)->coor.z,
// 			as_object(object)->light_brightness,
// 			(int)(as_object(object)->color.x * 255.999),
// 			(int)(as_object(object)->color.y * 255.999),
// 			(int)(as_object(object)->color.z * 255.999));
// 	else if (as_object(object)->type == CAMERA)
// 		printf("C	%.2f,%.2f,%.2f		%.2f,%.2f,%.2f	%f"
// 			"	# center orientation fov\n",
// 			as_object(object)->coor.x,
// 			as_object(object)->coor.y,
// 			as_object(object)->coor.z,
// 			as_object(object)->orientation.x,
// 			as_object(object)->orientation.y,
// 			as_object(object)->orientation.z,
// 			as_object(object)->camera_fov);
// 	else if (as_object(object)->type == PLANE)
// 		printf("pl	%.2f,%.2f,%.2f		%.2f,%.2f,%.2f	%d,%d,%d"
// 			"	# center orientation color\n",
// 			as_object(object)->coor.x,
// 			as_object(object)->coor.y,
// 			as_object(object)->coor.z,
// 			as_object(object)->orientation.x,
// 			as_object(object)->orientation.y,
// 			as_object(object)->orientation.z,
// 			(int)(as_object(object)->color.x * 255.999),
// 			(int)(as_object(object)->color.y * 255.999),
// 			(int)(as_object(object)->color.z * 255.999));
// 	else if (as_object(object)->type == SPHERE)
// 		printf("sp	%.2f,%.2f,%.2f		%.2f	%d,%d,%d"
// 			"	# center diameter color\n",
// 			as_object(object)->coor.x,
// 			as_object(object)->coor.y,
// 			as_object(object)->coor.z,
// 			as_object(object)->radius * 2,
// 			(int)(as_object(object)->color.x * 255.999),
// 			(int)(as_object(object)->color.y * 255.999),
// 			(int)(as_object(object)->color.z * 255.999));
// 	else if (as_object(object)->type == CYLINDER)
// 		printf(
// 			"cy	%.2f,%.2f,%.2f		%.2f,%.2f,%.2f	%.2f	%.2f	%d,%d,%d"
// 			"	# center orientation diameter height color\n",
// 			as_object(object)->coor.x,
// 			as_object(object)->coor.y,
// 			as_object(object)->coor.z,
// 			as_object(object)->orientation.x,
// 			as_object(object)->orientation.y,
// 			as_object(object)->orientation.z,
// 			as_object(object)->radius * 2,
// 			as_object(object)->height,
// 			(int)(as_object(object)->color.x * 255.999),
// 			(int)(as_object(object)->color.y * 255.999),
// 			(int)(as_object(object)->color.z * 255.999));
// 	else
// 		printf("# unknonw %d\n", as_object(object)->type);
// }
