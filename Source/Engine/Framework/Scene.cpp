#include "Scene.h"

#include "Framework/Components/CollisionComponent.h"
#include "Renderer/Renderer.h"
#include "Actor.h"

namespace ane {
	bool Scene::Initialize() {
		for(auto& actor : this->actors) {
			actor->Initialize();
		}

		return true;
	}

	void Scene::Update(float deltaTime) {
		// Remove destroyed actors and update non-destroyed actors
		auto iter = this->actors.begin();
		while(iter != this->actors.end()) {
			if((*iter)->active) {
				(*iter)->Update(deltaTime);
			}

			if((*iter)->destroyed) {
				iter = this->actors.erase(iter);
			} else {
				iter++;
			}
		}

		/*
		// Check collisions
		for(auto iter1 = this->actors.begin(); iter1 != this->actors.end(); iter1++) {
			for(auto iter2 = std::next(iter1, 1); iter2 != this->actors.end(); iter2++) {
				CollisionComponent* collision1 = (*iter1)->GetComponent<CollisionComponent>();
				CollisionComponent* collision2 = (*iter2)->GetComponent<CollisionComponent>();

				if(collision1 == nullptr || collision2 == nullptr) {
					continue;
				}

				if(collision1->CheckCollision(collision2)) {
					// boom
					(*iter1)->OnCollision(iter2->get());
					(*iter2)->OnCollision(iter1->get());
				}
			}
		}
		*/
	}

	void Scene::Draw(Renderer& renderer) {
		for(std::unique_ptr<Actor>& actor : this->actors) {
			if(actor->active) {
				actor->Draw(renderer);
			}
		}
	}

	void Scene::Add(std::unique_ptr<Actor> actor) {
		actor->scene = this;
		this->actors.push_back(std::move(actor));
	}

	void Scene::RemoveAll(bool force) {
		if(!force) {
			auto iter = this->actors.begin();
			while(iter != this->actors.end()) {
				if(!(*iter)->persistent) {
					iter = this->actors.erase(iter);
				} else {
					iter++;
				}
			}
		} else {
			this->actors.clear();
		}
	}

	bool Scene::Load(const std::string& fileName) {
		rapidjson::Document document;
		if(!JSON::Load(fileName, document)) {
			ERROR_LOG("Could not load scene file: " << fileName);
			return false;
		}

		Read(document);

		return true;
	}

	void Scene::Read(const JSON_t& value) {
		if(HAS_DATA(value, actors) && GET_DATA(value, actors).IsArray()) {
			for(auto& actorValue : GET_DATA(value, actors).GetArray()) {
				std::string type;
				READ_DATA(actorValue, type);

				auto actor = CREATE_CLASS_BASE(Actor, type);
				actor->Read(actorValue);

				if(actor->prototype) {
					std::string name = actor->name;
					Factory::Instance().RegisterPrototype(name, std::move(actor));
				} else {
					this->Add(std::move(actor));
				}
			}
		}
	}
}