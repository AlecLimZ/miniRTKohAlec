/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cameraray_notes.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <leng-chu@student.42kl.edu.m      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 19:00:19 by leng-chu          #+#    #+#             */
/*   Updated: 2022/10/02 20:16:01 by leng-chu         ###   ########.fr       */
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
//
//

#endif
