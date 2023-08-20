#pragma once

#include <string>

#include "Core/JSON.h"
#include "Factory.h"

// For headers
#define CLASS_DECLARATION(classname) \
		virtual const char* GetClassName() {return #classname;} \
		virtual void Read(const rapidjson::Value& value); \
		virtual std::unique_ptr<Object> Clone() {return std::make_unique<classname>(*this);} \
		class Register { \
			public: \
				Register() { \
					ane::Factory::Instance().Register<classname>(#classname); \
				} \
		};

// For source code
#define CLASS_DEFINITION(classname) classname::Register register_class

namespace ane {
	class Object {
		public:
			Object() = default;
			Object(const std::string& name) {this->name = name;}
			virtual ~Object() {OnDestroy();}

			CLASS_DECLARATION(Object);

			virtual bool Initialize() {return true;}
			virtual void OnDestroy() {;}

		public:
			std::string name;
			bool active = true;
	};
}