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

			Vector3  operator [] (size_t index) const {return rows[index];}
			Vector3& operator [] (size_t index) {return rows[index];}

			Vector2 operator * (const Vector2& v);
			Matrix3x3 operator * (const Matrix3x3& mx);

			static Matrix3x3 CreateScale(const Vector2& scale);
			static Matrix3x3 CreateScale(float scale);
			static Matrix3x3 CreateRotation(float radians);
			static Matrix3x3 CreateTranslation(const Vector2& translate);
			static Matrix3x3 CreateIdentity();

			Vector2 GetTranslation() const;
			float   GetRotation() const;
			Vector2 GetScale() const;
	};

	inline Vector2 Matrix3x3::operator * (const Vector2& v) {
		// | a b c |   | x |
		// | d e f | * | y |
		// | g h i |   | 1 |

		Vector2 result;
		result.x = rows[0][0] * v.x + rows[0][1] * v.y + rows[0][2] * 1;
		result.y = rows[1][0] * v.x + rows[1][1] * v.y + rows[1][2] * 1;

		return result;
	}

	inline Matrix3x3 Matrix3x3::operator * (const Matrix3x3& mx) {
		// | a b c |   | j k l |
		// | d e f | * | m n o |
		// | g h i |   | p q r |

		Matrix3x3 result;
		result[0][0] = rows[0][0] * mx[0][0] + rows[0][1] * mx[1][0] + rows[0][2] * mx[2][0];
		result[0][1] = rows[0][0] * mx[0][1] + rows[0][1] * mx[1][1] + rows[0][2] * mx[2][1];
		result[0][2] = rows[0][0] * mx[0][2] + rows[0][1] * mx[1][2] + rows[0][2] * mx[2][2];

		result[1][0] = rows[1][0] * mx[0][0] + rows[1][1] * mx[1][0] + rows[1][2] * mx[2][0];
		result[1][1] = rows[1][0] * mx[0][1] + rows[1][1] * mx[1][1] + rows[1][2] * mx[2][1];
		result[1][2] = rows[1][0] * mx[0][2] + rows[1][1] * mx[1][2] + rows[1][2] * mx[2][2];

		result[2][0] = rows[2][0] * mx[0][0] + rows[2][1] * mx[1][0] + rows[2][2] * mx[2][0];
		result[2][1] = rows[2][0] * mx[0][1] + rows[2][1] * mx[1][1] + rows[2][2] * mx[2][1];
		result[2][2] = rows[2][0] * mx[0][2] + rows[2][1] * mx[1][2] + rows[2][2] * mx[2][2];

		return result;
	}

	inline Matrix3x3 Matrix3x3::CreateScale(const Vector2& scale) {
		// | sx 0 0 |
		// | 0 sy 0 |
		// | 0  0 1 |

		Matrix3x3 matrix = CreateIdentity();
		matrix[0][0] = scale.x;
		matrix[1][1] = scale.y;

		return matrix;
	}

	inline Matrix3x3 Matrix3x3::CreateScale(float scale) {
		// | s 0 0 |
		// | 0 s 0 |
		// | 0 0 1 |

		Matrix3x3 matrix = CreateIdentity();
		matrix[0][0] = scale;
		matrix[1][1] = scale;

		return matrix;
	}

	inline Matrix3x3 Matrix3x3::CreateRotation(float radians) {
		// | c -s 0 |
		// | s  c 0 |
		// | 0  0 1 |

		Matrix3x3 matrix = CreateIdentity();
		float c = cos(radians);
		float s = sin(radians);

		matrix[0][0] = c;
		matrix[0][1] = -s;
		matrix[1][0] = s;
		matrix[1][1] = c;

		return matrix;
	}

	inline Matrix3x3 ane::Matrix3x3::CreateTranslation(const Vector2& translate) {
		// | 1 0 x |
		// | 0 1 y |
		// | 0 0 1 |

		Matrix3x3 matrix = CreateIdentity();
		matrix[0][2] = translate.x;
		matrix[1][2] = translate.y;

		return matrix;
	}

	inline Matrix3x3 Matrix3x3::CreateIdentity() {
		return Matrix3x3(Vector3(1, 0, 0), Vector3(0, 1, 0), Vector3(0, 0, 1));
	}

	inline Vector2 ane::Matrix3x3::GetTranslation() const {
		return Vector2(rows[0][2], rows[1][2]);
	}

	inline float ane::Matrix3x3::GetRotation() const {
		return std::atan2(rows[1][0], rows[0][0]);
	}

	inline Vector2 ane::Matrix3x3::GetScale() const {
		Vector2 x = Vector2(rows[0][0], rows[0][1]);
		Vector2 y = Vector2(rows[1][0], rows[1][1]);

		return Vector2(x.Length(), y.Length());
	}

	using mat3 = Matrix3x3;
}