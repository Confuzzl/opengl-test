#pragma once
#include "world/collision/polyhedron.h"

class Feature {
  Polyhedron &parent;
  const unsigned short ID;

  Feature(const Feature &f) = delete;
  Feature(Feature &&f) = delete;

protected:
  Feature(Polyhedron &parent, const unsigned short ID);
};
