#pragma once
#include "feature.h"
#include "edge.h"

class Face : public Feature {
  const std::vector<Edge*> edges;
  vec3 normal;

  Face(Polyhedron &parent, const unsigned short ID, const std::vector<Edge*> &edges);
};