#include "miniRT.h"

static bool	is_movable(int type)
{
	return (type == CAMERA || type == LIGHT || type == LIGHT_BONUS 
	|| type == SPHERE 
    // || type == PLANE  //todo
    || type == CYLINDER || type == CONE);
}

void	select_next(t_app *app)
{
	if (app->selected_object != NULL)
		app->selected_object = app->selected_object->next;
	if (app->selected_object == NULL)
		app->selected_object = app->objects;
	while (app->selected_object && !is_movable(((t_object *)app->selected_object->content)->type))
		app->selected_object = app->selected_object->next;
	if (app->selected_object == NULL)
		select_next(app);
}
