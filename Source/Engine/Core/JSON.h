#pragma once

#include <string>
#include <vector>

#include <rapidjson/include/rapidjson/document.h>

#define READ_DATA(value, data) ane::JSON::Read(value, #data, data)
#define READ_DATA_REQUIRED(value, data) ane::JSON::Read(value, #data, data, true)
#define READ_NAME_DATA(value, name, data) ane::JSON::Read(value, name, data)
#define READ_NAME_DATA_REQUIRED(value, name, data) ane::JSON::Read(value, name, data, true)
#define HAS_DATA(value, data) value.HasMember(#data)
#define GET_DATA(value, data) value[#data]

namespace ane {
	class JSON {
		public:
			static bool Load(const std::string& fileName, rapidjson::Document& document);
			static bool Read(const rapidjson::Value& value, const std::string& name, int& data, bool required = false);
			static bool Read(const rapidjson::Value& value, const std::string& name, float& data, bool required = false);
			static bool Read(const rapidjson::Value& value, const std::string& name, bool& data, bool required = false);
			static bool Read(const rapidjson::Value& value, const std::string& name, std::string& data, bool required = false);
			static bool Read(const rapidjson::Value& value, const std::string& name, class Vector2& data, bool required = false);
			static bool Read(const rapidjson::Value& value, const std::string& name, class Color& data, bool required = false);
			static bool Read(const rapidjson::Value& value, const std::string& name, class Rect& data, bool required = false);
			static bool Read(const rapidjson::Value& value, const std::string& name, std::vector<std::string>& data, bool required = false);
			static bool Read(const rapidjson::Value& value, const std::string& name, std::vector<int>& data, bool required = false);
	};

	using JSON_t = rapidjson::Value;
}