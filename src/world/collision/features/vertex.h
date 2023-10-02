#pragma once
class Edge;
#include "feature.h"
#include <memory>
#include <vector>

class Vertex : public Feature {
  std::vector<std::unique_ptr<Edge>> neighbors;
  vec3 localCoordinate;

public:
  Vertex(Polyhedron &parent, const unsigned short ID, const vec3 pos);
  ~Vertex();

  operator vec3() const;
};