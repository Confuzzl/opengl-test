#pragma once
#include "collision/polyhedron.h"
#include "collision/transformable.h"
#include "render/renderable.h"
#include "util/memory_utils.h"

class GameObject : public Transformable {
  UPtr<Polyhedron> collider;
  UPtr<Renderable> render;

public:
  const UPtr<Polyhedron> &getCollider();
  const UPtr<Renderable> &getRender();
};