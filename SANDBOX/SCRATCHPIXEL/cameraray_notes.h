/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cameraray_notes.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <leng-chu@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 19:00:19 by leng-chu          #+#    #+#             */
/*   Updated: 2022/10/05 19:15:33 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERARAY_NOTES_H
# define CAMERARAY_NOTES_H

// pseudocode
for (int j = 0; j < height; ++j)
{
	for (int i = 0; i < width; ++i)
	{
		//generate primary ray
		...
		// closest intersection, set to INFINITY to start with
		float tnear = INFINITY;
		for (int k = 0; k < numObjects; ++k) {
			// intersection to the current object if any
			float t = INFINITY;
			if (objects[k]->intersect(pimaryRay, tnear) && t < tnear)
			{
				tnear = t;
				framebuffer = objects[k].color;
			}
		}
	}
}

// the minimum requirement for defining a ray is a positon and a direction
Vec3f orig; // ray origin
Vec3f dir; // ray direction (normalized)

// P = orig + t * dir
// t is the distance from the origin to the point on the half-line.
// it can be either negative or positive
// if negative, the point on the ray is begind of the ray origin
// if positive, it is front of the ray origin.
// Practically, when we use ray-tracing, we only interested in finding
// the intersection of the ray with surfaces which is located at front
// ray's origin, so it means if t is positive then it is consider an
// intersection between a ray & a surface

// define ray's origin & direction
Vec3f orig = ...;
Vec3f dir = ...;
float t = INFINITY;
// does this ray intersect the object? intersect() reterns true if an intersection was found
if (object.intersect(orig, dir, t) && t > 0) {
	// this is a valid intersection, the hit point is in front of the ray's origin
}

// the equation above is called parametric equation.

Vec3f orig = ...;
Vec3f dir = ...;
float t = INFINITY;
if (object.intersect(orig, dir, t) && t > 0) {
	Vec3f hitPoint = orig + dir * t; // the point of the surface it hits
}


// Naturally the start of creating image is starting with rays
// knowns as primary or camera rays (primary is preferred)
// Secondary rays are shadow rays
// in ray-tracing, it is often 1 unit away from the camera's origin(eye)
// the eye(camerra)'s position origin - up: y-axis, right: x-axis, center direction from the origin: z-axis
// the z-axis can be either negative or positve
// our eyes but for this, using negative z-axis
// the line of a ray origin and directon is the vector from the camera's
// origin to pixel's center.
// 
// To compute the positon of a point at the center of a pixel,
// using raster space (expressed in coordinates(0,0) only
// from the top-left corner to world space
// world space is basically the space in which all objects of the scene,
// the geometry, the lights, and the camera have their coordinates
//
// to get the coordinates of the pixel in raster space and the same
// pixel inworld space, we will need to first normalize the pixel positino
// raster space coordination -> NDC screen (0 ~ 1) -> screen space (-1 ~ 1)
//
//Raster space coordination to NDC (Normalized Device Coordinates):
//PixelNDCx = (Pixelx + 0.5) / imageWidth
//PixelNDCy = (Pixely + 0.5) / imageHeight
//why 0.5 it is because we want to put the point in the CENTER of the
//SQUARE in NDC
//(square size is 1 x 1 so it makes sense that 0.5, 0.5 is center)
//
//When remapping 0,1 to -1,1 (from NDC to Screen space) we can correct by
// PixelScreenx = 2 * PixelNDCx - 1;
// PixelScreeny = 2 * PixelNDCy - 1;
// However this equation for y above is making y negative above the x
// so correct this problem for y is PixelScreeny = 1 - 2 * PixelNDCy
//

/** Image Aspect Ratio **/
// if 7 x 5, the pixel is not exactly square shape size
// therefore need to adjust only x-axis to make the pixel the square size
// by using formula 2 units(x-axis [-1, 1]) * 7 / 5 = 2.8 units
// so this case 2.8 units is [-1.4, 1.4] range to make the pixel square with unchanged
// y-axis while the image aspect ratio is 7 : 5
//

ImageAspectRatio = ImageWidth / ImageHeight
Pixelcamerax = (2 * PixelScreenx - 1) * ImageAspectRatio
Pixelcameray = (1 - 2 * PixelScreeny)


// finally we need to account for the field of view.
// since y coordinates is in range [-1, 1] so we know 1 unit between eye & screen(image plane)
// Because we know the distance from eye to the image plane and the height is 2 units
// we can use some simple trigonometry to find the angle of the right triangle ABC
// half of the vertical angle alpha
// alpha / 2 = atan(oppositeside / adjacentside) = atan(1 / 1) = π / 4;
//
// so in other word to get the length of BC, we only need to compute:
||BC|| = tan(alpha / 2);
// so bascially if alpha is greater than 90 degrees then BC is greater than 1
// otherwise if lower than 90 degrees then BC is lower than 1
#endif
Pixelcamerax = (2 * PixelScreenx - 1) * ImageAspectRatio * tan(alpha / 2);
Pixelcameray = (1 - 2 * PixelScreeny) * tan(alpha / 2);

// Since z-axis for the camera is negative so final point for the camera is
// (Pixelcamerax, Pixelcameray, -1)

// pseudo code
float imageAspectRatio = imageWidth / (float)imageHeight; // assuming width > height
float Px = (2 * ((x + 0.5) / imageWidth) - 1) * tan(fov / 2 * M_PI / 180) * imageAspectRatio;
float Py = (1 - 2 * ((y + 0.5) / imageHeight)) * tan(fov / 2 * M_PI / 180);
Vec3f rayOrigin(0);

// note that this just equal to Vec3f(Px, Py, -1);
Vec3f rayDirection = Vec3f(Px, Py, -1) - rayOrigin;
rayDirection = normalize(rayDirection); // it's a direction so don't forget to normalize

// once u set the camera point, u can move from its original position
// along the negative by using 4x4 matrix(translation & rotatio)
// matrix is known as camera-to-world matrix & world-to-camera matrix
// scaling a camera is not recommended
//
float imageAspectRatio = imageWidth / imageHeight;
float Px = (2 * ((x + 0.5) / imageWidth) - 1) * tan(fov / 2 * M_PI / 180) * imageAspectRatio;
float Py = (1 - 2 * ((y + 0.5) / imageHeight)) * tan(fov / 2 * M_PI / 180);
Vec3f rayOrigin = Point3(0, 0, 0);
Matrix44f cameraToWorld;
cameraToWorld.set(...); // set matrix
Vec3f rayOriginWorld, rayPWorld;
cameraToWorld.multVectMatrix(rayOrigin, rayOriginWorld);
cameraToWorld.multVectMatrix(Vec3f(Px, Py, -1), rayPWorld);
Vec3f rayDirection = rayPWorld - rayOriginWorld;
rayDirection.normalize(); // it's a direction so don't forget to normalize

// example source code about how the rays
// can be generated for each pixel of an image.
void render(
		const Options & options,
		const std::vector<std::unique_ptr<object> > & objects,
		const std::vector<std::unique_ptr<light> > & lights)
{
	Matrix44f cameraToWorld;
	Vec3f *framebuffer = new Vec3f[options.width * options.height];
	Vec3f *pix = framebuffer;
	float scale = tan(deg2rad(options.fov * 0.5));
	float imageAspectRatio = options.width / (float)options.height;
	Vec3f orig;
	cameraToWorld.multVecMatrix(Vec3f(0), orig);
	for (uint32_t j = 0; j < options.height; ++j) {
		for (uint32_t i = 0; i < options.width; ++i) {
			float x = (2 * (i + 0.5) / (float)options.width - 1) * imageAspectRatio * scale;
			float y = (1 - 2 * (j + 0.5) / (float)options.height) * scale;
			Vec3f dir;
			cameraToWorld.multDirMatrix(Vec3f(x, y, -1), dir);
			dir.normalize();
			*(pix++) = castRay(orig, dir, objects, lights, options, 0);
		}
	}

	// Save result to a PPM image (keep these flags if you compile under Windows)
	std::ofstream ofs("./out.ppm", std::ios::out | std::ios::binary);
	ofs << "P6\n" << options.width << " " << options.height << "\n255\n";
	for (uint32_t i = 0; i < options.height * options.width; ++i) {
		char r = (char)(255 * clamp(0, 1, framebuffer[i].x));
		char g = (char)(255 * clamp(0, 1, framebuffer[i].y));
		char b = (char)(255 * clamp(0, 1, framebuffer[i].z));
		ofs << r << g << b;
	}
	ofs.close();

	delete[] framebuffer;
} </std::unique_ptr<light></std::unique_ptr<object>

// functin raycast for the primary rays
Vec3f castRay (
			const Vec3f & orig, const Vec3f & dir,
			const std::vector<std::unique_ptr<Object> > &  objects,
			const std::vector<<std::unique_ptr<Light> > & lights,
			const Options & options,
			uint32_t depth
			)
{
	Vec3f hitColor = (dir + Vec3f(1)) * 0.5;
	return hitColor;
}

// other option for convert from pixel coordinate to NDC then screen space
// we can compute the ray direction as below
// dx = x - width / 2
// dy = height / 2 - y
// dz = -(height / 2) / tan (fov * 0.5)

// where x and y are the pixel's coordinates, and fov is the vertical field-of-view. Keep in mind that dz is negative because the camera by default is oriented along the negative z-axis.
Dx = (x - width / 2)ux + (height / 2 - y)vx - ((height / 2) / tan (fov * 0.5))wx;
Dy = (x - width / 2)uy + (height / 2 - y)vy - ((height / 2) / tan (fov * 0.5))wy;
Dz = (x - width / 2)uz + (height / 2 - y)vz - ((height / 2) / tan (fov * 0.5))wz;
//
//vector w (camera-to-world matrix) only need to do once,
//re-used each time new ray direction is created
//vector u, v & w is just the camera-to-world matrix's 3 points coordinate
Vec3f w_p = (-width / 2 ) * u + (height / 2) * v - ((height / 2) / tan(fov_rad * 0.5);
Vec3f ray_dir = normalize(x * u + y * (-v) + w_p);

// RENDERING SPHERES
class Object
{
	public:
	virtual bool intersect(const Vec3f & orig, const Vec3f & dir, float & bt) const = 0;
	virtual ~Object() {}
	Object() {}
};

class Sphere: public Object
{
	public:
	bool intersect(const Vec3f & orig, const Vec3f & dir, float & t) const
	{
		return false;
	}
};

int main(...)
{
	Sphere mySphere;
	...
		if (mySphere.intersect(orig, dir, t) {
					// this ray intersect this instance of the class Sphere
				}
}

// 2nd pseudo-code
class Sphere: public Object
{
	bool intersect(const Vec3f & orig, const Vec3f & dir, float & t) const
	{
		float t0, t1;
#if 0
		Vec3f L = center - orig;
		float tca = L.dotProduct(dir);
		if (tca < 0) return false;
		float d2 = L.dotProduct(L) - tca * tca;
		if (d2 > radius2) return false;
		float thc = sqrt(radius2 - d2);
		t0 = tca - thc;
		t1 = tca + thc;
#else
		Vec3f L = orig - center;
		float a = dir.dotProduct(dir);
		float b = 2 * dir.dotProduct(L);
		float c = L.dorProduct(L) - radius2;
		if (!solveQuadratic(a, b, c, t0, t1)) return false;
#endif
		if (t0 > t1) std::swap(t0, t1);
		if (t0 < 0) {
			t0 = t1;
			if (t0 < 0) return false;
		}
		t = t0;
		return true;
	}
};

// then compute the intersection of a ray with this geometry to the intersect
class TriangulatedMesh : public Object
{
	public:
		bool intersect(const Vec3f & orig, const Vec3f & dir, float & t) const
		{
			return true;
		}
};

// then creating a scene
int main(int argc, char **argv)
{
	// creating the scene (adding objects and lights)
	std::vector<std::unique_ptr<Object> > objects;

	// generate a scene made of random spheres
	uint32_t numSpheres = 32;
	gen.seed(0);
	for (uint32_t i = 0; i < numSpheres; ++i) {
		Vec3f randPos((0.5 - dis(gen)) * 10, (0.5 - dis(gen)) * 10, (0.5 + dis(gen) * 10));
		float randRadius = (0.5 + dis(gen) * 0.5);
		objects.push_back(std::unique_ptr<Object>(new Sphere(randPos, randRadius)));
	}

	// setting up options
	Options options;
	options.width = 640;
	options.height = 480;
	options.fov = 51.52;
	options.cameraToWorld = Matrix44f(0.945519, 0, -0.325569, 0, -0.179534, 0.834209l, -0.521403, 0, 0.271593, 0.551447, 0.78876, 0, 4.208271, 8.374532, 17.932925, 1);

	// finally, render
	render(options, objects);
	return (0);
}

// then render, make primary rays.
// origin & directon are transform by camera-to-world
void render(const Options &options, const std::vector<std::unique_ptr<Objects>> & objects)
{
	...
	float scale = tan(deg2rad(options.fov * 0.5));
	float imageAspectRatio = options.width / (float)options.height;
	Vec3f orig;
	options.cameraToWorld.multVecMatrix(Vec3f(0), orig);
	for (uint32_t j = 0; j < options.height, ++j) {
		for (uint32_t i = 0; i < options.width; ++i) {
			float x = (2 * (i + 0.5) / (float)options.width - 1) * imageAspectRatio * scale;
			float y = (1 - 2 * (j + 0.5) / (float)options.height) * scale;
			Vec3f dir;
			options.cameraToWorld.multDirMatrix(Vec3f(x, y, -1), dir);
			dir.normalize();
			*(pix++) = castRay(orig, dir, objects);
		}
	}
	// save to PPM image
}

// if intersect,return true
// trace() to keep track of the object withh closest intersection distance
// as the ray may intersect more than one object.

bool trace(const Vec3f & orig, const Vec3f & dir, const std::vector<std::unique_ptr<Object>> & objects, float & tNear, const Object * & hitObject)
{
	tNear = kInfinity;
	std::vector<std::unique_ptr<object>>::const_iterator iter= "objects.begin();" for="" (;="" !="objects.end(); " ++iter)="" { ="" float="" t="kInfinity;" if="" ((*iter)-="">intersect(orig, dir, t) && t < tNear) {
		hitObject = iter->getj();
		tNear = t;
		}
	}
	return (hitObject != nullptr);
}</std::unique_ptr<object>>::const_iterator>

/**Ray-Plane intersection**/
bool intersectPlane(const Vec3f & n, const Vec3f & p0, const Vec3f & 10, const Vec3f &l, float & t)
{
	// assuming vectors are all normalized
	float denom = dotProduct(n, 1);
	if (denom > 1e - 6) {
		Vec3f p010 = p0 - 10;
		t = dotProduct(p010, n) / denom;
		return (t >= 0);
	}
	return false;
}

// intersectDisk
// if distance is lower or equal to the disk radius, it means
// the ray intersects the disk
bool intersectDisk(const Vec3f & n, const Vec3f & p0, const float & radius, const Vec3f & l0, const Vec3 & l)
{
	float t = 0;
	if (intersectPlane(n, p0, l0, l, t)) {
		Vec3f p = 10 + l * t;
		Vec3f v = p - p0;
		float d2 = dot(v, v);
		return (sqrt(d2) <= radius);
		// or you can use the following optimisation (and precompute radius ^ 2)
		// return d2 <= radius2; // where radius2 = radius * radius
	}
	return false;
}

// computing the intersection of a ray with an AABB is
// y = mx + b
// m term is called the slope or gradient, responsible for the orientation
// of the line.
// b corresponds to the point where the line intersect the y-axis
// Thr ray can be expressed as: O + Dt
// which is very similar to the line equation y = mx + b
// so O replace with b and D with m
// to represent an axis-aligned bounding volumn, all we need are two points
// minimum & maximum extend of the box
class Box3
{
	public:
		Box3(const Vec3f & vmin, const Vec3f & vmax)
		{
			bounds[0] = vmin;
			bounds[1] = vmax;
		}
		Vec3f bounds[2];
};

// lets say line defined by the equation: y = B0x
// where B0x is the bounds[0].x
// to find where the ray intersects, we can write:
// Ox + tDx = B0x, which can solved by reordering the terms:
// t0x = (B0x - Ox) / Dx
