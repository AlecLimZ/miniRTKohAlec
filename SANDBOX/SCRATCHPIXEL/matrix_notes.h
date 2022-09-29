#ifndef MATRIX_NOTES_H
# define MATRIX_NOTES_H

//Matrix 
// Matrix is just a way of combinaing all transformations (scale, rotation, translation)
// into one single structure.
// for example we can create a matrix that will rotate 90 degrees around the x-axis, scale it by 2 along the z-axis(the scale applied to the point is (1, 1, 2), 
// then translate it by (-2, 3, 1)

// Can perform a succession of linear transformations without matrix
// but a lot coding as below:

Vec3f translate(Vec3f P, Vec3f translateValue) {...}
Vec3f scale(Vec3f P, Vec3f scaleValue) { ... }
Vec3f rotate(Vec3f P, Vec3f axis, float angle) { ... }

Vec3f P = Vec3f(1, 1, 1);
Vec3f translateVal(-1, 2, 4);
Vec3f scaleVal(1, 1, 2);
Vec3f axis(1, 0, 0);
float angle = 90;

Vec3f Pt;
Pt = translate(P, translateVal); // translate P
Pt = scale(Pt, scaleVal); // then scale the result
Pt = rotateValue(Pt, axis, angle); // rotate the point

// However if use matrix, coding is shorter

Matrix4f M(...); // set the matrix for translation, rotation, scale
Vec3f P = Vec3f(1, 1, 1);
Vec3f Ptransformed = P * M; // do everything at once by simply multiplying the point lol

template<typename T>
class Matrix44
{
	public:
		Matrix44() {}

		// access operator/accessor for both const & non-const
		// Matrx44f mat; mat[0][3] = 1.f will call these function.
		const t * operator [] (uint8_t i) const { return m[i]; }
		T *operator [] (uint8_t i) { return m[i]; }

		// initialize the coefficients of the matrix with the coefficients of the identity matrix
		T m[4][4] = {
			{1, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 1}
		};

		// multiply 2 matrices
		Matrix44 operator *(const Matrix44 & rhs) const
		{
			Matrix44 mult;
			for (uint8_t i = 0; i < 4; ++i)
			{
				for (uint8_t j = 0; j < 4; ++j)
				{
					mult[i][j] = m[i][0] * rhs[0][j] +
								m[i][1] * rhs[1][j] +
								m[i][2] * rhs[2][j] +
								m[i][3] * rhs[3][j];
				}
			}
			return multi;
		}
};

typedef Matrix44<float> Matrix44f;

/**Point-Matrix Multiplication Rules**/
// multiply coeffs from row 1 to row 3 with coeffs from column 1
Ptransformed.x = P.x * c00 + P.y * c10 + P.z * c20

// multiply coeffecs from row 1 to row 3 with coeffs from column 2
Ptransformed.y = P.x * c01 + P.y * c11 + P.z * c21

// multiply coeffecs from row 1 to row 3 with coeffs from column 3
Ptransformed.z = P.x * c02 + P.y * c12 + P.z * c22


/**The identity Matrix**/
|	1 0 0	|
|	0 1 0	|
|	0 0 1	|

// multiplying P by the identity matrix gives P
Ptransformed.x = P.x * 1 + P.y * 0 + P.z * 0 = P.x;
Ptransformed.y = P.x * 0 + P.y * 1 + P.z * 0 = P.y;
Ptransformed.z = P.x * 0 + P.y * 0 + P.z * 1 = P.z;


/** The scaling matrix **/
// when the coefficient(along the diagonal for the identity Matrix) are different from 1
// it means it is acting as multiplier for the scaled up or down by some amount

|	Sx 0 0	|
|	0 Sy 0	|
|	0 0 Sz	|

// multiplying P by the scaling matrix
Ptransformed.x = P.x * Sx + P.y * 0 + P.z * 0 = P.x * Sx;
Ptransformed.y = P.x * 0 + P.y * Sy + P.z * 0 = P.y * Sy;
Ptransformed.z = P.x * 0 + P.y * 0 + P.z * Sz = P.z * Sz;

/**Rotation Matrix**/

// for Z-axis rotation (counterclockwise 90 degrees)
// px = 1, py = 0, pz = 0;
Pt.x = P.x * 0 + P.y * 1 + P.z * 0 = 0;
Pt.y = P.x * 1 + P.y * 0 + P.z * 0 = 1;
Pt.z = P.x * 0 + P.y * 0 + P.z * 1 = 0;

// trigonometric knowledge
// tx = cos(θ) = 0
// ty = sin(θ) = 1
// θ = π / 2
// therefore it works for the rotation(90 degrees) around the z-axis as below:

|	cos(θ) sin(θ) 0	|
|	sin(θ) cos(θ) 0	|
|	  0      0    1	|

// if want 45 degree, then set to π / 4

// if clockwise then as below
|	cos(θ) sin(θ)  0	|
|	-sin(θ) cos(θ) 0	|
|	   0      0    1	|

// if X-axis rotation (clockwise 90 degrees)
|	1   0      0		|
|	0 cos(θ) sin(θ)		|
|	0 -sin(θ) cos(θ)	|

Pt.x = P.x * 1 + P.y * 0 + P.z * 0;
Pt.y = P.x * 0 + P.y * 0 + P.z * 1;
Pt.z = P.x * 0 + P.y * -1 + P.z * 0;

// if Y-axis rotation (clockwise 90 degrees)
|	cos(θ) 0 -sin(θ)	|
|	  0    1   0		|
|	sin(θ) 0 cos(θ)		|

Pt.x = P.x * 0 + P.y * 0 + P.z * -1;
Pt.y = P.x * 0 + P.y * 1 + P.z * 1;
Pt.z = P.x * 1 + P.y * 0 + P.z * 0;

// matrix rotation then translation
p.x = p.x * m00 + p.y * m10 + p.z * m20 + Tx
p.y = p.x * m01 + p.y * m11 + p.z * m21 + Ty
p.z = p.x * m02 + p.y * m12 + p.z * m22 + Tz

// if the column has four coefficients instead of 3, then
// assuming the matrix is size 4 x 3
p.x = p.x * m00 + p.y * m10 + p.z * m20 + m30
p.y = p.x * m01 + p.y * m11 + p.z * m21 + m31
p.z = p.x * m02 + p.y * m12 + p.z * m22 + m32

// if 1 x 3 matrix with 4 x 3 matrix, theory tells this is not possible
// but there is a simple solution is:
// add one extra column to make 1x3 into 1x4, set the 4th as 1
// (x, y, z, 1) is called as homogeneous point or homogeneous coordinate
p.x = p.x * m00 + p.y * m10 + p.z * m20 + 1 * m30
p.y = p.x * m01 + p.y * m11 + p.z * m21 + 1 * m31
p.z = p.x * m02 + p.y * m12 + p.z * m22 + 1 * m32
// because the fourth value is always 1 which is why coding didn't show the 1 while only define the x, y and z. 
// therefore coding below is working same as the pervious coding above
// for the 4th point formula...
p.x = p.x * m00 + p.y * m10 + p.z * m20 + m30
p.y = p.x * m01 + p.y * m11 + p.z * m21 + m31
p.z = p.x * m02 + p.y * m12 + p.z * m22 + m32

// if make a multiplicaton of an homogeneous point by [4x4] matrix
// then 4th row is known as w coordinate of the transformed point
// alway set to (0, 0, 0, 1) so w is 
// w = x * 0 + y + 0 + z * 0 + w(=1) * 1 = 1
// may not always to (0, 0, 0, 1) if deal with projecton matrices
p.x = p.x * m00 + p.y * m10 + p.z * m20 + m30
p.y = p.x * m01 + p.y * m11 + p.z * m21 + m31
p.z = p.x * m02 + p.y * m12 + p.z * m22 + m32
w	= p.x * m03 + p.y * m13 + p.z * m23 + m33;

// normalize w back to the 1 if the result for w is not 1 or 0
if (w != 1 && w != 0) {
	p.x /= w, p.y /= w, p.z /= w;
}
// the homogeneous coordinates is not used in ray tracing..
// but it is for the Perspective & Orthographic Projection Matrix


/**Transforming Vectors**/

// vector don't need to be translated coz their positon is meaningless
// vector is in the directon which they point and their length is 
// an information that we need to solve geometric or shading problem.

V.x = V.x * M00 + V.y * M10 + V.z * M20;
V.y = V.x * M01 + V.y * M11 + V.z * M21;
V.z = V.x * M02 + V.y * M12 + V.z * M22;

void multDirMatrix(const Vec3<T> & src, Vec3<T> & dst) const
{
	dst.x = src.x * m[0][0] + src.y * m[1][0] + src.z * m[2][0];
	dst.y = src.x * m[0][1] + src.y * m[1][1] + src.z * m[2][1];
	dst.z = src.x * m[0][2] + src.y * m[1][2] + src.z * m[2][2];
}

#endif
