#pragma once
class Face;
class Vertex;
#include "feature.h"
#include <memory>
#include <vector>

class Edge : public Feature {
  const Vertex &tail, &head;
  std::shared_ptr<Face> cw, ccw;

public:
  Edge(Polyhedron &parent, const unsigned short ID, const Vertex &tail,
       const Vertex &head);
  ~Edge();

  operator vec3() const;
};