#pragma once

#include <string>

namespace ane {
	class Object {
		public:
			Object() = default;
			Object(const std::string& name) {this->name = name;}
			virtual ~Object() {OnDestroy();}

			virtual bool Initialize() {return true;}
			virtual void OnDestroy() {;}

		protected:
			std::string name;
	};
}