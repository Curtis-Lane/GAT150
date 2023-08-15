#pragma once

#include <string>

#include "Core/JSON.h"
#include "Factory.h"

// For headers
#define CLASS_DECLARATION(classname) \
		virtual const char* GetClassName() {return #classname;} \
		bool Read(const rapidjson::Value& value); \
		class Register { \
			public: \
				Register() { \
					Factory::Instance().Register<classname>(#classname); \
				} \
		};

// For source code
#define CLASS_DEFINITION(classname) classname::Register register_class;

namespace ane {
	class Object {
		public:
			Object() = default;
			Object(const std::string& name) {this->name = name;}
			virtual ~Object() {OnDestroy();}

			CLASS_DECLARATION(Object);

			virtual bool Initialize() {return true;}
			virtual void OnDestroy() {;}

		protected:
			std::string name;
	};
}