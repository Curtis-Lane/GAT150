#pragma once

#include "Singleton.h"

#include <memory>
#include <map>
#include <string>

#include "Core/Logger.h"

#define CREATE_CLASS(classname) ane::Factory::Instance().Create<ane::classname>(#classname)
#define CREATE_CLASS_BASE(classbase, classname) ane::Factory::Instance().Create<ane::classbase>(classname)
#define INSTANTIATE(classbase, classname) ane::Factory::Instance().Create<classbase>(classname)

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

	template<typename T>
	class PrototypeCreator : public CreatorBase {
		public:
			PrototypeCreator(std::unique_ptr<T> prototype) {this->prototype = std::move(prototype);}
			std::unique_ptr<class Object> Create() override {
				return this->prototype->Clone();
			}

		private:
			std::unique_ptr<T> prototype;
	};

	class Factory : public Singleton<Factory> {
		public:
			template<typename T>
			void Register(const std::string& key);

			template<typename T>
			void RegisterPrototype(const std::string& key, std::unique_ptr<T> prototype);

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
	inline void Factory::RegisterPrototype(const std::string& key, std::unique_ptr<T> prototype) {
		INFO_LOG("Prototype Class registered: " << key);

		this->registry[key] = std::make_unique<PrototypeCreator<T>>(std::move(prototype));
	}

	template<typename T>
	inline std::unique_ptr<T> Factory::Create(const std::string& key) {
		auto iter = this->registry.find(key);
		if(iter != this->registry.end()) {
			return std::unique_ptr<T>(dynamic_cast<T*>(iter->second->Create().release()));
		}

		ERROR_LOG("Class not found in Factory: " << key);

		return std::unique_ptr<T>();
	}
}