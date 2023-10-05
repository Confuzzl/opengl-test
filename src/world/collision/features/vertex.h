#pragma once
class Edge;
#include "feature.h"
#include "util/memory_utils.h"
#include "util/vector_utils.h"

class Vertex : public Feature {
  Vector<SPtr<Edge>> neighbors;
  Vec3 localCoordinate;

public:
  Vertex(Polyhedron &parent, const unsigned short ID, const Vec3 pos);
  //~Vertex();

  operator Vec3() const;
};