#pragma once
#include "world/collision/polyhedron.h"

//template <typename T>
class Feature {
  Polyhedron &parent;
  unsigned short ID;

  Feature(Polyhedron &parent, const unsigned short ID);
};
