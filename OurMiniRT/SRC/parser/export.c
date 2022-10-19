#include "miniRT.h"

void	export_scene(t_list *object)
{
	if (object->next)
		export_scene(object->next);
	if (as_object(object)->type == AMBIENT)
		printf("A	%.2f	%d,%d,%d"
			"	# ratio color\n",
			as_object(object)->ambient_ratio,
			(int)(as_object(object)->color.x * 255.999),
			(int)(as_object(object)->color.y * 255.999),
			(int)(as_object(object)->color.z * 255.999));
	else if (as_object(object)->type == LIGHT)
		printf("L	%.2f,%.2f,%.2f		%.2f	%d,%d,%d"
			"	# center brightness color\n",
			as_object(object)->coor.x,
			as_object(object)->coor.y,
			as_object(object)->coor.z,
			as_object(object)->light_brightness,
			(int)(as_object(object)->color.x * 255.999),
			(int)(as_object(object)->color.y * 255.999),
			(int)(as_object(object)->color.z * 255.999));
	else if (as_object(object)->type == CAMERA)
		printf("C	%.2f,%.2f,%.2f		%.2f,%.2f,%.2f	%f"
			"	# center orientation fov\n",
			as_object(object)->coor.x,
			as_object(object)->coor.y,
			as_object(object)->coor.z,
			as_object(object)->orientation.x,
			as_object(object)->orientation.y,
			as_object(object)->orientation.z,
			as_object(object)->camera_fov);
	else if (as_object(object)->type == PLANE)
		printf("pl	%.2f,%.2f,%.2f		%.2f,%.2f,%.2f	%d,%d,%d"
			"	# center orientation color\n",
			as_object(object)->coor.x,
			as_object(object)->coor.y,
			as_object(object)->coor.z,
			as_object(object)->orientation.x,
			as_object(object)->orientation.y,
			as_object(object)->orientation.z,
			(int)(as_object(object)->color.x * 255.999),
			(int)(as_object(object)->color.y * 255.999),
			(int)(as_object(object)->color.z * 255.999));
	else if (as_object(object)->type == SPHERE)
		printf("sp	%.2f,%.2f,%.2f		%.2f	%d,%d,%d"
			"	# center diameter color\n",
			as_object(object)->coor.x,
			as_object(object)->coor.y,
			as_object(object)->coor.z,
			as_object(object)->radius * 2,
			(int)(as_object(object)->color.x * 255.999),
			(int)(as_object(object)->color.y * 255.999),
			(int)(as_object(object)->color.z * 255.999));
	else if (as_object(object)->type == CYLINDER)
		printf("cy	%.2f,%.2f,%.2f		%.2f,%.2f,%.2f		%.2f	%.2f	%d,%d,%d"
			"	# center orientation diameter height color\n",
			as_object(object)->coor.x,
			as_object(object)->coor.y,
			as_object(object)->coor.z,
			as_object(object)->orientation.x,
			as_object(object)->orientation.y,
			as_object(object)->orientation.z,
			as_object(object)->radius * 2,
			as_object(object)->height,
			(int)(as_object(object)->color.x * 255.999),
			(int)(as_object(object)->color.y * 255.999),
			(int)(as_object(object)->color.z * 255.999));
	else
		printf("# unknonw %d\n", as_object(object)->type);
}
