#pragma once
#include "edge.h"
#include "feature.h"
#include <memory>
#include <vector>

class Face : public Feature {
  const std::vector<std::unique_ptr<Edge>> edges;
  vec3 normal;

  Face(Polyhedron &parent, const unsigned short ID,
       const std::vector<std::unique_ptr<Edge>> &edges);

  vec3 calculateNormal();
};