
// Vector is a direction in 3D space, represented by 3 numbers.
template<typename T>
class Vec3
{
	public:
		// 3 most basic ways of initializing a vector
		Vec3() : x(T(0)), y(T(0)), z(T(0)) {}
		Vec3(const T & xx) : x(xx), y(xx), z(xx) {}
		Vec3(T xx, T yy, T zz) : x(xx), y(yy), z(zz) {}
		T x, y, z;

	public:
		// symbol ||V|| means a length of a vector
		T length() // 1st option: length of a vector
		{
			return sqrt(x * x + y * y + z* z);
		}

		// 1st option: normalize a vector (make range become between 0 - 1)
		// normalize a vector is called as Euclidean norm
		Vec3<T> & normalize()
		{
			T len = length();
			if (len > 0)
			{
				T invLen = 1 / len;
				x *= invLen, y *= invLen, z *= invLen;
			}
			return (*this);
		}

		// Dot product/scalar ||V||² = V.V
		// if dot product return 1 means B is on exactly same direction as A
		// if dot product return -1 means B is opposite direction of A's direction
		// if dot product return 0  means B is on perpendicular(at angle of 90°) from A
		T dot(const Vec3<T> & v) const
		{
			return x * v.x + y * v.y + z * v.z;
		}

		Vec3<T> & normalize_dot()
		{
			T len2 = dot(*this);
			if (len2 > 0)
			{
				T invLen = 1 / sqrt(len2);
				x *= invLen, y *= invLen, z *= invLen;
			}
			return (*this);
		}

		// Cross product C = A x B 
		
		/**Formule to get Cross (vector c)**/
		// Cx = Ay * Bz - Az * By;
		// Cy = Az * Bx - Ax * Bz;
		// Cz = Ax * By - Ay * Bx;

		// Cross return a vector (C) while dot returns a number
		// C is perpendicular(always due to the formula above) to both A and B
		// both A and B dont have to be perpendicular to each other
		// both A and B define the plane and produce a vector C
		// A, B & C forms a cartesian coordinate system if all are unit length
		// if B x A instead of A x B, it give -C, means the cross is anticommutative
		// anticommutative means swapping the position of any two arguments negates result
		// So swapping never be same result but inverse. 
		// Unique solution is alwiz same from each unique combination of A and B. 
		Vec3<T> cross(const Vec3<T> & v) const
		{
			return Vec3<T> (
					y * v.z - z * v.y,
					z * v.x - x * v.z,
					x * v.y - y * v.x);
		}

		// vector/point addition and subtraction
		
		// looks like used translation movement to me
		Vec3<T> operator+(const Vec3<T> & v) const
		{
			return Vec3<T>(x + v.x, y + v.y, z + v.z);
		}

		// looks like used for translation movement to me
		Vec3<T> operator-(const Vec3<T> & v) const
		{
			return Vec3<T>(x - v.x, y - v.y, z - v.z);
		}

		// looks like used for scale to me
		Vec<T> operator * (const T & r) const
		{
			return Vec3<T>(x * r, y * r, z * r);
		}
};
// Unit vector is a vector which has unit length



//2nd option without being a part of a class - length of a vector
template<typename T>
T length(Vec3<T> const & v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

//2nd option dot
template<typename T>
T dot(const Vec3<T> & a, const Vec3<T> & b)
{
	return a.x * b.x + a.y * a.y * b.y + a.z * b.z;
}

//2nd option cross as utility function
template<typename T>
Vec3<T> cross(const vec3<T> & a, const Vec3<T> & b)
{
	return Vec3<T>(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x);
}

//2nd option without being a part of a class - length of a vector
template<typename T>
void normalize(Vec3<T> & v)
{
	T len2 = v.x * v.x + v.y * v.y + v.z * v.z;
	if (len2 > 0) //  avoid division by 0
	{
		T invLen = 1 / sqrt(len2);
		x *= invLen, y *= invLen, z *= invLen;
	}
}
