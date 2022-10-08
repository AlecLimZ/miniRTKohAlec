#include <math.h>
void	rotate_x(float *y, float *z, double angle_x)
{
	float	previous_y;

	previous_y = *y;
	*y = previous_y * cos(angle_x) - *z * sin(angle_x);
	*z = previous_y * sin(angle_x) + *z * cos(angle_x);
}

/*rotate about y-axis anticlockwise about angle_y*/
void	rotate_y(float *x, float *z, double angle_y)
{
	float	previous_x;

	previous_x = *x;
	*x = previous_x * cos(angle_y) + *z * sin(angle_y);
	*z = -previous_x * sin(angle_y) + *z * cos(angle_y);
}

/*rotate about z-axis anticlockwise about angle_z*/
void	rotate_z(float *x, float *y, double angle_z)
{
	float	previous_x;
	float	previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = previous_x * cos(angle_z) - previous_y * sin(angle_z);
	*y = previous_x * sin(angle_z) + previous_y * cos(angle_z);
}
