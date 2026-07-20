#pragma once
#include <cstdint>

struct Entity {
	uint32_t id;

	bool operator==(const Entity e) const {
		return id == e.id;
	}
};