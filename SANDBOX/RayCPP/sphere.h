#ifndef SPHERE_H
# define SPHERE_H

# include "hittable.h"
# include "vec3.h"

class sphere : public hittable
{
	public:
		sphere() {}
		sphere(point3 cen, double r) : center(cen), radius(r){}

		virtual bool hit(const ray & r, double t_min, double t_max, hit_record & rec) const override;

	public:
		point3 center;
		double radius;
};

bool sphere::hit(const ray & r, double t_min, double t_max, hit_record & rec) const
{
	vec3 oc = r.getOrigin() - center;
	double a = r.getDirection().length_squared();
	double half_b = dot(oc, r.getDirection());
	double c = oc.length_squared() - radius * radius;

	double discriminant = half_b * half_b - a * c;
	if (discriminant < 0) return false;
	double sqrtd = sqrt(discriminant);

	// Find the nearest root that lies in the acceptable range.
	double root = (-half_b - sqrtd) / a;
	if (root < t_min || t_max < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < t_min || t_max < root)
			return (false);
	}
	rec.t = root;
	rec.p = r.getAt(rec.t);
	//rec.normal = (rec.p - center) / radius;
	vec3 outward_normal = (rec.p - center) / radius;
	rec.set_face_normal(r, outward_normal);

	return (true);
}

#endif
