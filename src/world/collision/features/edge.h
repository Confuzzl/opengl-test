#pragma once
class Face;
class Vertex;
#include "feature.h"
#include "util/memory_utils.h"
#include "util/vector_utils.h"

class Edge : public Feature {
  const Vertex &tail, &head;
  SPtr<Face> cw, ccw;

public:
  Edge(Polyhedron &parent, const unsigned short ID, const Vertex &tail,
       const Vertex &head);
  //~Edge();

  operator Vec3() const;
};