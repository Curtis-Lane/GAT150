#pragma once

#include <list>

#include "Actor.h"

namespace ane {
	class Renderer;

	class Scene {
		public:
			Scene() = default;

			bool Initialize();
			void Update(float deltaTime);
			void Draw(Renderer& renderer);

			void Add(std::unique_ptr<Actor> actor);
			void RemoveAll(bool force = false);

			bool Load(const std::string& fileName);
			void Read(const JSON_t& value);

			template<typename T>
			T* GetActor();

			template<typename T = Actor>
			T* GetActorByName(const std::string& name);

		private:
			std::list<std::unique_ptr<Actor>> actors;
	};

	template<typename T>
	inline T* Scene::GetActor() {
		for(std::unique_ptr<Actor>& actor : this->actors) {
			T* result = dynamic_cast<T*>(actor.get());
			if(result != nullptr) {
				return result;
			}
		}

		return nullptr;
	}

	template<typename T>
	inline T* Scene::GetActorByName(const std::string& name) {
		for(std::unique_ptr<Actor>& actor : this->actors) {
			if(actor->name == name) {
				T* result = dynamic_cast<T*>(actor.get());
				if(result != nullptr) {
					return result;
				}
			}
		}

		return nullptr;
	}
}