#pragma once
#include "edge.h"
#include "feature.h"
#include <memory>
#include <vector>

class Vertex : public Feature {
  std::vector<std::unique_ptr<Edge>> neighbors;
  vec3 localCoordinate;

  Vertex(Polyhedron &parent, const unsigned short ID, const vec3 pos);

public:
  operator vec3() const;
};