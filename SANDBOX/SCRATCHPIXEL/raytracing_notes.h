#ifndef RAYTRACING_NOTES_H
# define RAYTACING_NOTES_H

// for each pixel on the image, our eyes shoots a primary ray to each pixel frm the scene
// After the primary ray direction is set and check if every object is interseatc with any of them based on the light source direction
// if not found then it is illuminated, if found then casts a shadow on the pixel
// algorithm for raytacing in pseudocode:
for (int j = 0; j < imageHeight; ++j)
{
	for (int i = 0; i < imageWidth; ++i)
	{
		// compute primary ray direction
		Ray primRay;
		computePrimRay(i, j, &primRay);

		// shoot prim ray in the scene and search for intersection
		Point pHit;
		Normal nHit;
		float minDist = INFINITY;
		Object object = NULL;
		for (int k = 0; k < objects.size(); ++k)
		{
			if (Intersect(objects[k], primRay, &pHit, &nHit))
			{
				float distance = Distance(eyePosition, pHit);
				if (distance < minDistance)
				{
					object = objects[k];
					minDistance = distance; // update min distance
				}
			}
		}
		if (object != NULL)
		{
			// compute illumination
			/Ray shadowRay;
			shadowRay.direction = lightPositon - pHit;
			bool isShadow = false;
			for (int k = 0; k < objects.size(); ++k)
			{
				if (Intersect(objects[k], shadowRay))
				{
					isInShadow = true;
					break ;
				}
			}
		}
		if (!isInShadow)
			pixels[i][j] = object->color * light.brightness;
		else
			pixel[i][j] = 0;
	}
}

#endif
