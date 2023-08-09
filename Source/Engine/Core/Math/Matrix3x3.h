#pragma once

#include "Vector2.h"
#include "Vector3.h"

namespace ane {
	class Matrix3x3 {
		public:
			Vector3 rows[3];
			// [row][column]
			// rows[0] = Vector3( 0, 0, 0 )
			// rows[1] = Vector3( 0, 0, 0 )
			// rows[2] = Vector3( 0, 0, 0 )

			Matrix3x3() = default;
			Matrix3x3(const Vector3& row1, const Vector3& row2, const Vector3& row3) {rows[0] = row1; rows[1] = row2; rows[2] = row3;}

			Vector3  operator [] (size_t index) const {
				return rows[index];
			}
			Vector3& operator [] (size_t index) {
				return rows[index];
			}

			Vector3 operator * (const Vector3& v);
			Matrix3x3 operator * (const Matrix3x3& mx);

			static Matrix3x3 CreateScale(const Vector2& scale);
			static Matrix3x3 CreateScale(float scale);
			static Matrix3x3 CreateRotation(float radians);

			static Matrix3x3 CreateIdentity();
	};

	inline Vector3 Matrix3x3::operator * (const Vector3& v) {
		// | a b | * | x |
		// | c d | * | y |

		Vector3 result;
		result.x = rows[0][0] * v.x + rows[0][1] * v.y;
		result.y = rows[1][0] * v.x + rows[1][1] * v.y;

		return result;
	}

	inline Matrix3x3 Matrix3x3::operator * (const Matrix3x3& mx) {
		// | a b |   | e f |
		// | c d | * | g h |

		Matrix3x3 result;
		result[0][0] = rows[0][0] * mx[0][0] + rows[0][1] * mx[1][0];
		result[0][1] = rows[0][0] * mx[0][1] + rows[0][1] * mx[1][1];
		result[1][0] = rows[1][0] * mx[0][0] + rows[1][1] * mx[1][0];
		result[1][1] = rows[1][0] * mx[0][1] + rows[1][1] * mx[1][1];

		return result;
	}

	inline Matrix3x3 Matrix3x3::CreateScale(const Vector2& scale) {
		Matrix3x3 matrix = CreateIdentity();
		matrix[0][0] = scale.x;
		matrix[1][1] = scale.y;

		return matrix;
	}

	inline Matrix3x3 Matrix3x3::CreateScale(float scale) {
		Matrix3x3 matrix = CreateIdentity();
		matrix[0][0] = scale;
		matrix[1][1] = scale;

		return matrix;
	}

	inline Matrix3x3 Matrix3x3::CreateRotation(float radians) {
		Matrix3x3 matrix = CreateIdentity();
		float c = cos(radians);
		float s = sin(radians);

		matrix[0][0] = c;
		matrix[0][1] = -s;
		matrix[1][0] = s;
		matrix[1][1] = c;

		return matrix;
	}

	inline Matrix3x3 Matrix3x3::CreateIdentity() {
		return Matrix3x3(Vector3(1, 0, 0), Vector3(0, 1, 0), Vector3(0, 0, 1));
	}

	using mat3 = Matrix3x3;
}