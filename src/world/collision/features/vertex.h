#pragma once
#include "feature.h"
#include "face.h"

class Vertex : public Feature {
  //Edge *neighbors[];
  const std::vector<Edge *> neighbors;
  vec3 localCoordinate;

  Vertex(Polyhedron &parent, const unsigned short ID, const vec3 pos);
};