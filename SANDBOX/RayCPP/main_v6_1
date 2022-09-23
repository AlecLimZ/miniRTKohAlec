/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 17:43:23 by leng-chu          #+#    #+#             */
/*   Updated: 2022/09/22 17:19:12 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <iostream>
#include "vec3.h"
#include "color.h"
#include "ray.h"

// hit on the sphere
double	hit_sphere(const point3 & center, double radius, const ray & r)
{
	vec3	oc = r.getOrigin() - center;
	double	a = dot(r.getDirection(), r.getDirection());
	double	b = 2.0 * dot(oc, r.getDirection());
	double	c = dot(oc, oc) - radius * radius;
	double	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return -1.0;
	else
		return (-b - sqrt(discriminant)) / (2.0 * a);
}

// color is vec3 class - but role is color
color ray_color(const ray & r)
{
	// unit_vector is returning v / v.length() which
	// calling inline vec3 operator/(vec3 v, double t) return 
	// (1 / t) * v which calling vec3 operator*(double t, const vec3 & v)
	// return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
//	if (hit_sphere(point3(0, 0, -1), 0.5, r))
//		return color(1, 0, 0);
	double	t = hit_sphere(point3(0, 0, -1), 0.5, r);
	if (t > 0.0)
	{
		vec3 N = unit_vector(r.getAt(t) - vec3(0, 0, -1));
		return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
	}
	vec3	unit_direction = unit_vector(r.getDirection());
	t = 0.5 * (unit_direction.y() + 1.0);
	//return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
	return (1.0 - t) * color(1.0, 1.0, 1.0) + (t) * color(0.5, 0.7, 1.0);
}

int main()
{
	// Image
	const double	aspect_ratio = 16.0 / 9.0;
	const int	image_width = 400;
	const int	image_height = static_cast<int>(image_width / aspect_ratio);

	// Camera
	double	viewport_height = 2.0;
	double	viewport_width = aspect_ratio * viewport_height;
	double	focal_length = 1.0;

	point3	origin = point3(0, 0, 0);
	vec3	horizontal = vec3(viewport_width, 0, 0);
	vec3	vertical = vec3(0, viewport_height, 0);
	vec3	lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

	// Render
	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; --j)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < image_width; ++i)
		{
			double u = double(i) / (image_width - 1);
			double v = double(j) / (image_height - 1);
			ray	r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
			color pixel_color = ray_color(r);
			write_color(std::cout, pixel_color);
		}
	}
	std::cerr << "\nDone.\n";
}
