#include "Object.h"

namespace ane {
	void Object::Read(const rapidjson::Value& value) {
		READ_DATA(value, name);
	}
}