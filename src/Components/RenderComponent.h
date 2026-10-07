#pragma once

#include <memory>

#include "../Graphics/Mesh.h"
#include "../Graphics/Material.h"

struct RenderComponent
{
	std::shared_ptr<Mesh> mesh;
	std::shared_ptr<Material> material;
};