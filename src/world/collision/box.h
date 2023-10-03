#pragma once
#include "polyhedron.h"

class Box : public Polyhedron<Box> {
public:
  Box(const std::vector<vec3> &coordinates);
  static consteval unsigned short triCount();
};