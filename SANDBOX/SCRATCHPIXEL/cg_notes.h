#ifndef CG_NOTES_H
# define CG_NOTES_H

// example a box has 8 corners = 8 points
// corner 1 : (0, 0, 0) <=== origin
// corner 2: (12, 0, 0)
// corner 3: (12, 8, 0)
// corner 4: (0, 8, 0)
// corner 5: (0, 0, 10)
// corner 6: (12, 0, 10)
// corner 7: (12, 8, 10)
// corner 8: (0, 8, 10)

typedef float Point[3];
int main()
{
	Point corners[8] = {
		{0, 0, 0},
		{12, 0, 0},
		{12, 8, 0},
		{0, 8, 0},
		{0, 0, 10},
		{12, 0, 10},
		{12, 8, 10},
		{0, 8, 10},
	};
	return 0;
}

//two important things to complete the process for the 3D:
//1. a system defines how the eight points are connected to make a box
//this is called the topology of the object, an object also called as a model
//Topology refers to how points we call vertices are connected to form faces or flat surfaces
//these faces are also called polygons. So the box would be
//made of total six faces or six polygons. The set of polygons are known as
//polygonal mesh or mesh.

//2. A system to create an image of that box which requires to project the corners(points) of the box
//onto the imaginary canvas, this process is known as perspective projection.

typedef float Point[3];
int main()
{
	Point corners[8] = {
		{ 1, -1, -5},
         { 1, -1, -3},
         { 1,  1, -5},
         { 1,  1, -3},
         {-1, -1, -5},
         {-1, -1, -3},
         {-1,  1, -5},
         {-1,  1, -3}
	};

	// 3D become 2D here but 2D still can draw 8 points
	for (int i = 0; i < 8; ++i) {
		// divide the x and y coordinates by the z coordinate to
		// project the point on the canvas
		float x_proj = corners[i][0] / -corners[i][2];
		float y_proj = corners[i][1] / -corners[i][2];
		printf("projected corner: %d x:%f y:%f\n", i, x_proj, y_proj);
	}
	return 0;
}


// if there is 2 units for x-axis, means range is -1, 0, 1
// however negative and positive are not easy to manipulate
// so normalize -1, 0, 1 into 0, 1 by remap as below
float x_proj remap = (1 + x_proj) / 2;
float y_proj_remap = (1 + y_proj) / 2;

// if the point is out range of the 0, 1. it is called NDC space
// NDC = Normalized Device Coordinates
// Digital Image is just 2D pixel.
// lets say 512x512 image has 512 rows of 512 pixels

const unsigned int image_width = 512, image_height = 512;

for (int i = 0; i < 8; ++i) {
	float x_proj = corners[i][0] / -corners[i][2];
	float y_proj = corners[i][1] / -corners[i][2];

	float x_proj remap = (1 + x_proj) / 2;
	float y_proj_remap = (1 + y_proj) / 2;

	float x_proj_pix = x_proj_remap * image_width;
	float y_proj_pix = y_proj_remap * image_height;
	printf("corner: %d x:%f y:%f\n", i, x_proj_pix, y_proj_pix);
	return (0);
}
// however above do not output an image yet but only 8 dots within image's area
//
//
#endif
