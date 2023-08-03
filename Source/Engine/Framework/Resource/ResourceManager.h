#pragma once

#include <map>
#include <memory>
#include <string>

#include "Resource.h"

namespace ane {
	class ResourceManager {
		public:
			template<typename T, typename ... TArgs>
			std::shared_ptr<T> Get(const std::string& fileName, TArgs ... args);

		private:
			std::map<std::string, std::shared_ptr<Resource>> resources;
	};

	template<typename T, typename ... TArgs>
	inline std::shared_ptr<T> ResourceManager::Get(const std::string& fileName, TArgs ... args) {
		if(this->resources.find(fileName) != this->resources.end()) {
			return std::dynamic_pointer_cast<T>(this->resources[fileName]);
		}

		std::shared_ptr<T> resource = std::make_shared<T>();
		resource->Create(fileName, args...);
		this->resources[fileName] = resource;

		return resource;
	}

	extern ResourceManager globalResourceManager;
}