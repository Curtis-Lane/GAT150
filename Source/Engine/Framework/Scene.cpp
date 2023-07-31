#include "Scene.h"

#include "Renderer/Renderer.h"
#include "Actor.h"

namespace ane {
	void Scene::Update(float deltaTime) {
		// Remove destroyed actors and update non-destroyed actors
		auto iter = this->actors.begin();
		while(iter != this->actors.end()) {
			(*iter)->Update(deltaTime);

			if((*iter)->destroyed) {
				iter = this->actors.erase(iter);
			} else {
				iter++;
			}
		}

		// Check collisions
		for(auto iter1 = this->actors.begin(); iter1 != this->actors.end(); iter1++) {
			for(auto iter2 = std::next(iter1, 1); iter2 != this->actors.end(); iter2++) {
				float distance = (*iter1)->transform.position.Distance((*iter2)->transform.position);
				float radius = (*iter1)->GetRadius() + (*iter2)->GetRadius();

				if(distance <= radius) {
					// boom
					(*iter1)->OnCollision(iter2->get());
					(*iter2)->OnCollision(iter1->get());
				}
			}
		}
	}

	void Scene::Draw(Renderer& renderer) {
		for(std::unique_ptr<Actor>& actor : this->actors) {
			actor->Draw(renderer);
		}
	}

	void Scene::Add(std::unique_ptr<Actor> actor) {
		actor->scene = this;
		this->actors.push_back(std::move(actor));
	}

	void Scene::RemoveAll() {
		this->actors.clear();
	}
}