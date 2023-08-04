#pragma once

#include <map>
#include <memory>
#include <string>

#include "Resource.h"

namespace ane {
	class ResourceManager {
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

	extern ResourceManager globalResourceManager;
}