#pragma once

#include <list>
#include "Actor.h"

namespace ane {
	class Renderer;

	class Scene {
		public:
			Scene() = default;

			void Update(float deltaTime);
			void Draw(Renderer& renderer);

			void Add(std::unique_ptr<Actor> actor);
			void RemoveAll();

			template<typename T>
			T* GetActor();

			//friend class Actor;

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
}