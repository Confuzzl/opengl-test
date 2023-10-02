#pragma once
#include "face.h"
#include "feature.h"
#include "vertex.h"
#include <vector>

class Edge : public Feature {
  const Vertex &tail, &head;
  std::unique_ptr<Face> cw, ccw;

  Edge(Polyhedron &parent, const unsigned short ID, const Vertex &tail,
       const Vertex &head);

public:
  operator vec3() const;
};