#include "WorldSerializer.h"
#include "../World/World.h"
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>


using json = nlohmann::json;

bool saveWorld(const World& w, const std::string& filename) {
	json scene;
	scene["entities"] = json::array();

	for (const auto& e : w.getEntities()) {
		json j_e;
		j_e["id"] = e.id;
		json comps = json::array();

		if (const auto* t = w.getComp<TransformComponent>(e)) {
			json j_comp;
			j_comp["type"] = "TransformComponent";
			j_comp["data"] = *t;
			comps.push_back(j_comp);
		}

		if (const auto* h = w.getComp<HealthComponent>(e)) {
			json j_comp;
			j_comp["type"] = "HealthComponent";
			j_comp["data"] = *h;
			comps.push_back(j_comp);
		}

		j_e["components"] = comps;
		scene["entities"].push_back(j_e);
	}

	std::ofstream out(filename);

	if (!out) {
		std::cerr << "Error: can`t open file: " << filename << std::endl;
		return false;
	}

	out << scene.dump(4);
	return true;
}

bool loadWorld(World& w, const std::string& filename) {
	std::ifstream in(filename);

	if (!in) {
		std::cerr << "Error: can`t open file: " << filename << std::endl;
		return false;
	}

	json scene;

	try {
		in >> scene;
	}
	catch (const json::parse_error& e) {
		std::cerr << "Error: fail to parse json: " << e.what() << std::endl;
		return false;
	}

	auto& entities = w.getEntities();

	while (!entities.empty()) {
		w.removeEntity(entities.back());
	}

	if (!scene.contains("entities") || !scene["entities"].is_array()) {
		std::cerr << "Error: missing entities array" << std::endl;
		return false;
	}

	for (const auto& j_e : scene["entities"]) {
		Entity e = w.createEntity();
		if (!j_e.contains("components") || j_e["components"].empty()) {
			continue;
		}

		for (const auto& j_comp : j_e["components"]) {
			if (!j_comp.contains("type") || !j_comp.contains("data")) {
				std::cerr << "Error: component without 'data'" << std::endl;
				return false;
			}

			const std::string& type = j_comp["type"];

			try {
				if (type == "TransformComponent") {
					TransformComponent comp = j_comp["data"].get<TransformComponent>();
					*w.addComp<TransformComponent>(e) = comp;
				}
				else if (type == "HealthComponent") {
					HealthComponent comp = j_comp["data"].get<HealthComponent>();
					*w.addComp<HealthComponent>(e) = comp;
				}
				else {
					std::cerr << "Warning: unknown component type: " << type << std::endl;
				}
			}
			catch (const json::exception& e) {
				std::cerr << "Error: component serialization" << e.what() << std::endl;
				return false;
			}
		}
	}
	return true;
}