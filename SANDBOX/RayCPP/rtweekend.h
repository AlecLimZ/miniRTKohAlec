#ifndef RTWEEKEND_H
# define RTWEEKEND_H

# include <cmath>
# include <limits>
# include <memory>

// using 
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

//constants
const double	infinity = std::numeric_limits<double>::infinity();
const double	pi = 3.1415926535897932385;

// Utility functions
inline double	degrees_to_radians(double degrees)
{
	return degrees * pi / 180.0;
}

// Common Headers
# include "vec3.h"
# include "ray.h"

inline double random_double()
{
	return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max)
{
	return min + (max - min) * random_double();
}

//alternate implementation for random double
// inline double random_double() {
// static std::uniform_real_distribution<double> distribution(0.0, 1.0);
// static std::mt19937 generator;
// return distribution(generator);
// }

inline double clamp(double x, double min, double max)
{
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

void	write_color(std::ostream & out, color pixel_color, int samples_per_pixel)
{
	double	r = pixel_color.x();
	double	g = pixel_color.y();
	double	b = pixel_color.z();

	// Divide the color by the number of samples.
	double scale = 1.0 / samples_per_pixel;
	r *= scale;
	g *= scale;
	b *= scale;

	// Write the translated [0, 255] value of each color component.
	out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
		<< static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
		<< static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

#endif
