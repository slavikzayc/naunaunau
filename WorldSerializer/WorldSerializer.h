#pragma once

#include <string>

class World;

bool saveWorld(const World& w, const std::string& filename);
bool loadWorld(World& w, const std::string& filename);