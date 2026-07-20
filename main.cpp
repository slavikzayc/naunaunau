#include "World/World.h"
#include "Systems/MovementSystem.h"
#include <iostream>
#include "WorldSerializer/WorldSerializer.h"


int main() {
	World w;

	Entity e1 = w.createEntity();
	Entity e2 = w.createEntity();

	TransformComponent* t_comp1 = w.addComp<TransformComponent>(e1);
	TransformComponent* t_comp2 = w.addComp<TransformComponent>(e2);

	t_comp1->pos_x = 15;
	t_comp1->pos_y = 23;
	t_comp1->pos_z = 14;
	
	std::cout << "Before:" << std::endl;

	std::cout << t_comp1->pos_x << ' ' << t_comp1->pos_y << ' ' << t_comp1->pos_z << std::endl;
	std::cout << t_comp2->pos_x << ' ' << t_comp2->pos_y << ' ' << t_comp2->pos_z << std::endl;

	w.update(0.016f);
	w.update(0.016f);
	w.update(0.016f);

	std::cout << "After:" << std::endl;

	std::cout << t_comp1->pos_x << ' ' << t_comp1->pos_y << ' ' << t_comp1->pos_z << std::endl;
	std::cout << t_comp2->pos_x << ' ' << t_comp2->pos_y << ' ' << t_comp2->pos_z << std::endl;
}