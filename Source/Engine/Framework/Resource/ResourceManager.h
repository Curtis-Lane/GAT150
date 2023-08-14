#pragma once

#include "Framework/Singleton.h"

#include <map>
#include <memory>
#include <string>

#include "Resource.h"

#define GET_RESOURCE(type, fileName, ...) ane::ResourceManager::Instance().Get<type>(fileName, __VA_ARGS__)

namespace ane {
	class ResourceManager : public Singleton<ResourceManager> {
		public:
			template<typename T, typename ... TArgs>
			res_t<T> Get(const std::string& fileName, TArgs ... args);

		private:
			std::map<std::string, res_t<Resource>> resources;
	};

	template<typename T, typename ... TArgs>
	inline res_t<T> ResourceManager::Get(const std::string& fileName, TArgs ... args) {
		if(this->resources.find(fileName) != this->resources.end()) {
			return std::dynamic_pointer_cast<T>(this->resources[fileName]);
		}

		res_t<T> resource = std::make_shared<T>();
		resource->Create(fileName, args...);
		this->resources[fileName] = resource;

		return resource;
	}
}