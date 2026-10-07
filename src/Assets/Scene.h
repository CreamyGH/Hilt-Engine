#pragma once

#include <entt/entt.hpp>

class Scene
{
public:
	virtual void OnCreate() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnDestroy() = 0;

public:
	entt::registry sceneRegistry;
};