#pragma once
class Edge;
#include "feature.h"
#include <memory>
#include <vector>

class Face : public Feature {
  const std::vector<std::unique_ptr<Edge>> edges;
  vec3 normal;

  vec3 calculateNormal();

  public:
  Face(Polyhedron &parent, const unsigned short ID,
       const std::vector<std::unique_ptr<Edge>> &edges);
  ~Face();
};