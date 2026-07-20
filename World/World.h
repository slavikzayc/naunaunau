#pragma once

#include "../Components/Components.h"
#include "../Components/Entity.h"
#include <unordered_map>
#include <memory>
#include <typeindex>

class World {
 private:
	 uint32_t next_id = 1;

	 struct ICompPool {
		 virtual ~ICompPool() = default;
		 virtual void remove(Entity e) = 0;
	 };

	 template <typename T>
	 struct CompPool : public ICompPool{
		 std::unordered_map<uint32_t, std::unique_ptr<T>> pool_;
		 void remove(Entity e) override { pool_.erase(e.id); }
	 };

	 // хранение всех пулов по индексу
	 std::unordered_map<std::type_index, std::unique_ptr<ICompPool>> comps;

	 std::vector<Entity> entities;

	 template <typename T>
	 CompPool<T>& getOrCreatePool();

	 template <typename T>
	 const CompPool<T>* getPool() const;

	 template <typename T>
	 CompPool<T>* getPool();



public:
	Entity createEntity();
	void removeEntity(Entity e);

	template <typename T>

	T* addComp(Entity e);

	template <typename T>
	const T* getComp(Entity e) const;

	template <typename T>
	T* getComp(Entity e);

	const std::vector<Entity>& getEntities() const;
	std::vector<Entity>& getEntities();

	template <typename T>
	bool hasComp(Entity e) const;

	void update(float dt);

};


template <typename T>
World::CompPool<T>& World::getOrCreatePool() {
	auto type = std::type_index(typeid(T));
	auto [iter, flag] = comps.try_emplace(type, nullptr);

	if (flag)
		iter->second = std::make_unique<CompPool<T>>();


	return static_cast<CompPool<T>&>(*iter->second);
	
}

template <typename T>
const World::CompPool<T>* World::getPool() const {
	auto type = std::type_index(typeid(T));
	auto iter = comps.find(type);

	if (iter == comps.end()) {
		return nullptr;
	}

	return static_cast<CompPool<T>*>(iter->second.get());
}

template <typename T>
World::CompPool<T>* World::getPool() {
	auto type = std::type_index(typeid(T));
	auto iter = comps.find(type);

	if (iter == comps.end()) return nullptr;

	return static_cast<CompPool<T>*>(iter->second.get());
}

template <typename T>
T* World::addComp(Entity e) {
	auto& pool = getOrCreatePool<T>();
	auto comp = std::make_unique<T>();
	T* ptr = comp.get();
	pool.pool_[e.id] = std::move(comp);
	return ptr;
}

template <typename T>
const T* World::getComp(Entity e) const {
	const auto* pool = World::getPool<T>();

	if (!pool) return nullptr;

	auto iter = pool->pool_.find(e.id);

	if (iter == pool->pool_.end()) return nullptr;

	return iter->second.get();
}

template <typename T>
T* World::getComp(Entity e) {
	auto* pool = getPool<T>();

	if (!pool) return nullptr;

	auto iter = pool->pool_.find(e.id);

	if (iter == pool->pool_.end()) return nullptr;

	return iter->second.get();
}

template <typename T>
bool World::hasComp(Entity e) const {
	const auto* pool = getPool<T>();

	if (!pool) return false;

	auto iter = pool->pool_.find(e.id);

	if (iter == pool->pool_.end()) return false;

	return true;
}
