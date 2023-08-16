#pragma once

#include "Singleton.h"

#include <memory>
#include <map>
#include <string>

#include "Core/Logger.h"

#define CREATE_CLASS(classname) ane::Factory::Instance().Create<ane::classname>(#classname);
#define CREATE_CLASS_BASE(classbase, classname) ane::Factory::Instance().Create<ane::classbase>(classname);

namespace ane {
	class CreatorBase {
		public:
			virtual ~CreatorBase() = default;

			virtual std::unique_ptr<class Object> Create() = 0;
	};

	template<typename T>
	class Creator : public CreatorBase {
		public:
			std::unique_ptr<class Object> Create() override {
				return std::make_unique<T>();
			}
	};

	class Factory : public Singleton<Factory> {
		public:
			template<typename T>
			void Register(const std::string& key);

			template<typename T>
			std::unique_ptr<T> Create(const std::string& key);

			friend class Singleton;

		protected:
			Factory() = default;

		private:
			std::map<std::string, std::unique_ptr<CreatorBase>> registry;
	};

	template<typename T>
	inline void Factory::Register(const std::string& key) {
		INFO_LOG("Class registered: " << key);

		this->registry[key] = std::make_unique<Creator<T>>();
	}

	template<typename T>
	inline std::unique_ptr<T> Factory::Create(const std::string& key) {
		auto iter = this->registry.find(key);
		if(iter != this->registry.end()) {
			return std::unique_ptr<T>(dynamic_cast<T*>(iter->second->Create().release()));
		}

		return std::unique_ptr<T>();
	}
}