#pragma once
#include "polyhedron.h"

class Box : public Polyhedron {
public:
  Box(const Vec3List &coordinates);
  static consteval unsigned short triCount();
};