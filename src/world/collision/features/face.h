#pragma once
class Edge;
#include "feature.h"
#include "util/memory_utils.h"
#include "util/vector_utils.h"

class Face : public Feature {
  const Vector<Edge> edges;
  Vec3 normal;

  Vec3 calculateNormal();

public:
  Face(Polyhedron &parent, const unsigned short ID, const Vector<Edge> &edges);
  //~Face();
};