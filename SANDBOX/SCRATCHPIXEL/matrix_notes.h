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
#endif
