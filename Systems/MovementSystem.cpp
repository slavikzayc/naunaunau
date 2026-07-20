#include "MovementSystem.h"
#include "../Components/Components.h"

void movementSystem(float vel_x, float vel_y, float vel_z, World& w, float dt) {
	auto entities = w.getEntities();

	for (auto e : entities) {
		if (w.hasComp<TransformComponent>(e))
		{
			auto* comp = w.getComp<TransformComponent>(e);
			comp->pos_x += vel_x * dt;
			comp->pos_y += vel_y * dt;
			comp->pos_z += vel_z * dt;
		}
	}
}