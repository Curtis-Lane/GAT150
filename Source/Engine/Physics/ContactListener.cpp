#include "ContactListener.h"

#include <box2d/include/box2d/box2d.h>

#include "Framework/Components/CollisionComponent.h"
#include "Framework/Actor.h"

namespace ane {
	void ContactListener::BeginContact(b2Contact* contact) {
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		if(fixtureA->GetUserData().pointer && fixtureB->GetUserData().pointer) {
			Actor* actorA = reinterpret_cast<Actor*>(fixtureA->GetUserData().pointer);
			Actor* actorB = reinterpret_cast<Actor*>(fixtureB->GetUserData().pointer);

			if(actorA->destroyed || actorB->destroyed) return;
			if(actorA == nullptr || actorB == nullptr) return;

			actorA->OnCollisionEnter(actorB);
			actorB->OnCollisionEnter(actorA);
		}
	}

	void ContactListener::EndContact(b2Contact* contact) {
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		if(fixtureA->GetUserData().pointer && fixtureB->GetUserData().pointer) {
			Actor* actorA = reinterpret_cast<Actor*>(fixtureA->GetUserData().pointer);
			Actor* actorB = reinterpret_cast<Actor*>(fixtureB->GetUserData().pointer);

			if(actorA->destroyed || actorB->destroyed) return;
			if(actorA == nullptr || actorB == nullptr) return;

			actorA->OnCollisionExit(actorB);
			actorB->OnCollisionExit(actorA);
		}
	}
}