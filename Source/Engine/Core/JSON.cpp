#include "JSON.h"

#include <sstream>

#include <rapidjson/include/rapidjson/istreamwrapper.h>

#include "Math/Vector2.h"
#include "FileIO.h"
#include "Logger.h"

namespace ane {
	bool JSON::Load(const std::string& fileName, rapidjson::Document& document) {
		std::string buffer;
		if(!readFile(fileName, buffer)) {
			WARNING_LOG("Cannot open file: " << fileName);
			return false;
		}

		std::stringstream stream(buffer);
		rapidjson::IStreamWrapper istream(stream);

		// Parse stream to JSON
		document.ParseStream(istream);
		if(!document.IsObject()) {
			WARNING_LOG("JSON file cannot be parsed: " << fileName);
			return false;
		}

		return true;
	}

	bool JSON::Read(const rapidjson::Value& value, const std::string& name, int& data, bool required) {
		if(!value.HasMember(name.c_str()) || !value[name.c_str()].IsInt()) {
			if(required) {
				ERROR_LOG("Cannot read required JSON data: " << name.c_str());
			}
			return false;
		}

		data = value[name.c_str()].GetInt();

		return true;
	}

	bool JSON::Read(const rapidjson::Value& value, const std::string& name, float& data, bool required) {
		if(!value.HasMember(name.c_str()) || !value[name.c_str()].IsFloat()) {
			if(required) {
				ERROR_LOG("Cannot read required JSON data: " << name.c_str());
			}
			return false;
		}

		data = value[name.c_str()].GetFloat();

		return true;
	}

	bool JSON::Read(const rapidjson::Value& value, const std::string& name, bool& data, bool required) {
		if(!value.HasMember(name.c_str()) || !value[name.c_str()].IsBool()) {
			if(required) {
				ERROR_LOG("Cannot read required JSON data: " << name.c_str());
			}
			return false;
		}

		data = value[name.c_str()].GetBool();

		return true;
	}

	bool JSON::Read(const rapidjson::Value& value, const std::string& name, std::string& data, bool required) {
		if(!value.HasMember(name.c_str()) || !value[name.c_str()].IsString()) {
			if(required) {
				ERROR_LOG("Cannot read required JSON data: " << name.c_str());
			}
			return false;
		}

		data = value[name.c_str()].GetString();

		return true;
	}

	bool JSON::Read(const rapidjson::Value& value, const std::string& name, Vector2& data, bool required) {
		// Check if 'name' member exists and is an array with 2 elements
		if(!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 2) {
			if(required) {
				ERROR_LOG("Cannot read required JSON data: " << name.c_str());
			}
			return false;
		}

		// Create JSON array object
		auto& array = value[name.c_str()];
		// Get array values
		for(rapidjson::SizeType i = 0; i < array.Size(); i++) {
			if(!array[i].IsNumber()) {
				ERROR_LOG("Invalid JSON data type: " << name.c_str());
				return false;
			}

			data[i] = array[i].GetFloat();
		}
		
		return true;
	}
}