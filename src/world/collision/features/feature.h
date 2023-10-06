#pragma once
#include "world/collision/polyhedron.h"

class Feature {
public:
  const Polyhedron &parent;
  const unsigned short ID;

protected:
  Feature(Polyhedron &parent, const unsigned short ID);
  // Feature(const Feature &f) = default;
  // Feature(Feature &&f) = default;
};
