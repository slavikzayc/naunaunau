#include "World.h"
#include "../Systems/MovementSystem.h"

Entity World::createEntity() {
	Entity e{ next_id++ };
	entities.push_back(e);
	return e;
}

void World::removeEntity(Entity e) {
	for (auto& [type, pool] : comps) {
		pool->remove(e);
	}
	std::erase(entities, e);
}

const std::vector<Entity>& World::getEntities() const {
	return entities;
}

std::vector<Entity>& World::getEntities() {
	return entities;
}


void World::update(float dt) {
	movementSystem(2.f, 4.f, 8.f, *this, dt);
}
