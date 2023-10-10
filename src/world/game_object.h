#pragma once
class Polyhedron;
class Renderable;
#include "collision/transformable.h"
#include "util/memory_utils.h"

class GameObject : public Transformable {
  UPtr<Polyhedron> collider;
  UPtr<Renderable> render;

  GameObject(UPtr<Polyhedron> &&collider, UPtr<Renderable> &&render);

public:
  const UPtr<Polyhedron> &getCollider();
  const UPtr<Renderable> &getRender();
};