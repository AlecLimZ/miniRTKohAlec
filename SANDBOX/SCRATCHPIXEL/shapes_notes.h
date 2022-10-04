#ifndef SHAPES_NOTES_H
# define SHAPES_NOTES_H

// Parametric equation of a sphere:
P.x = cos(θ) sin(ϕ);
P.y = cos(θ);
P.z = sin(θ) sin(ϕ);

// Ray-Sphere Intersection
bool	solveQuadratic(const float & a, const float & b, const float & c, float & x0, float &x1)
{
	float discr = b * b - 4 * a * c;
	if (discr < 0) return false;
	else if (discr == 0) x0 = x1 = -0.5 * b / a;
	else {
		float q = (b > 0) ?
			-0.5 * (b + sqrt(discr)) :
			-0.5 * (b - sqrt(discr));
		x0 = q / a;
		x1 = c / q;
	}
	if (x0 > x1) std::swap(x0, x1);
	return true;
}

bool intersect(const Ray & ray) const
{
	float t0, t1; // solutions for t if the ray intersects
#if 0
	// geometric solution
	Vec3f L = center - orig;
	float tca = L.dotProduct(dir);
	// if (tca < 0) return false;
	float thc = sqrt(radius2 - d2);
	t0 = tca - thc;
	t1  = tca + thc;
#else
	// analytic solution
	Vec3f L = orig - center;
	float a = dir.dotProduct(dir);
	float b = 2 * dir.dotProduct(L);
	float c = L.dotProduct(L) - radius2;
	if (!solveQuadratic(a, b, c, t0, t1)) return false;
#endif
	if (t0 > t1) std::swap(t0, t1);
	if (t0 < 0) {
		t0 = t1; // if t0 is negative, let's use t1 instead
		if (t0 < 0) return false; // both t0 and t1 are negative
	}
	t = t0;
	return true;
}

#endif
