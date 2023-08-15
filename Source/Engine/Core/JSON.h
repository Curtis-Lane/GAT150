#pragma once

#include <string>

#include <rapidjson/include/rapidjson/document.h>

#define READ_DATA(value, data) ane::JSON::Read(value, #data, data);
#define READ_DATA_REQUIRED(value, data) ane::JSON::Read(value, #data, data, true);

namespace ane {
	class JSON {
		public:
			static bool Load(const std::string& fileName, rapidjson::Document& document);
			static bool Read(const rapidjson::Value& value, const std::string& name, int& data, bool required = false);
			static bool Read(const rapidjson::Value& value, const std::string& name, float& data, bool required = false);
			static bool Read(const rapidjson::Value& value, const std::string& name, bool& data, bool required = false);
			static bool Read(const rapidjson::Value& value, const std::string& name, std::string& data, bool required = false);
			static bool Read(const rapidjson::Value& value, const std::string& name, class Vector2& data, bool required = false);
	};
}