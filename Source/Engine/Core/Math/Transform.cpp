#include "Transform.h"

namespace ane {
	void Transform::Read(const JSON_t& value) {
		READ_DATA(value, position);
		READ_DATA(value, rotation);
		READ_DATA(value, scale);
	}
}