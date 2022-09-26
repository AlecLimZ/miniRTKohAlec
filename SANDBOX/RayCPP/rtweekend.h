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

#endif