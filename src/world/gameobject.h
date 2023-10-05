#pragma once
#include "collision/polyhedron.h"
#include "collision/transformable.h"
#include "render/renderable.h"
#include <memory>

class GameObject : public Transformable {
  std::unique_ptr<Polyhedron> collider;
  std::unique_ptr<Renderable> render;

public:
  const std::unique_ptr<Polyhedron> &getCollider() { return collider; }
};