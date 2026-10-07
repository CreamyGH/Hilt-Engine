#pragma once

#include <memory>

#include "../Assets/Mesh.h"
#include "../Assets/Material.h"

struct RenderComponent
{
	std::shared_ptr<Mesh> mesh;
	std::shared_ptr<Material> material;
};