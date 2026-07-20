#pragma once
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct Component{
	virtual ~Component() = default;
};


struct TransformComponent : public Component {
	float pos_x, pos_y, pos_z;
	float rX, rY, rZ;
	float scale_x, scale_y, scale_z;
	TransformComponent() = default;
};

struct HealthComponent : public Component {
	int hp, max_hp;
	HealthComponent() = default;
};


// функции необходимые для работы с либой
inline void to_json(json& j, const TransformComponent& c) {
	j = json{
		{"pos_x", c.pos_x} , {"pos_y", c.pos_y} , {"pos_z", c.pos_z} ,
		{"rX", c.rX} , {"rY", c.rY} , {"rZ", c.rZ} ,
		{"scale_x", c.scale_x} , {"scale_y", c.scale_y} , {"scale_z", c.scale_z}
	};
}

inline void from_json(const json& j, TransformComponent& c) {
	j.at("pos_x").get_to(c.pos_x);
	j.at("pos_y").get_to(c.pos_y);
	j.at("pos_z").get_to(c.pos_z);
	j.at("rX").get_to(c.rX);
	j.at("rY").get_to(c.rY);
	j.at("rZ").get_to(c.rZ);
	j.at("scale_x").get_to(c.scale_x);
	j.at("scale_y").get_to(c.scale_y);
	j.at("scale_z").get_to(c.scale_z);
}

inline void to_json(json& j, const HealthComponent& c) {
	j = json{
		{"hp", c.hp} , {"max_hp", c.max_hp}
	};
}


inline void from_json(const json& j, HealthComponent& c) {
	j.at("hp").get_to(c.hp);
	j.at("max_hp").get_to(c.max_hp);
}